#include "ntp.h"

#include <string.h>
#include <time.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/dns.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"

volatile struct tm *utc = NULL;
volatile struct tm *current_utc = NULL;

static void ntp_result(NTP_T* state, int status, time_t *result)
{
    if (status == 0 && result)
    {
        // *result += TIMEZONE_OFFSET;
        if (!utc)
            utc = gmtime(result);
        current_utc = gmtime(result);
        printf("Got NTP response: %02d/%02d/%04d %02d:%02d:%02d\n", current_utc->tm_mday, current_utc->tm_mon + 1, current_utc->tm_year + 1900, current_utc->tm_hour, current_utc->tm_min, current_utc->tm_sec);
    }

    if (state->ntp_resend_alarm > 0)
    {
        cancel_alarm(state->ntp_resend_alarm);
        state->ntp_resend_alarm = 0;
    }
    state->ntp_test_time = make_timeout_time_ms(NTP_TEST_TIME);
    state->dns_request_sent = false;
}

static void ntp_request(NTP_T *state)
{
    cyw43_arch_lwip_begin();
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, NTP_MSG_LEN, PBUF_RAM);
    uint8_t *req = (uint8_t *) p->payload;
    memset(req, 0, NTP_MSG_LEN);
    req[0] = 0x1b;
    udp_sendto(state->ntp_pcb, p, &state->ntp_server_address, NTP_PORT);
    pbuf_free(p);
    cyw43_arch_lwip_end();
}

static int64_t ntp_failed_handler(alarm_id_t id, void *user_data)
{
    NTP_T* state = (NTP_T*)user_data;
    printf("NTP request failed\n");
    ntp_result(state, -1, NULL);
    return 0;
}

static void ntp_dns_found(const char *hostname, const ip_addr_t *ipaddr, void *arg)
{
    NTP_T *state = (NTP_T*)arg;
    if (ipaddr)
    {
        state->ntp_server_address = *ipaddr;
        printf("NTP address %s\n", ipaddr_ntoa(ipaddr));
        ntp_request(state);
    }
    else
    {
        printf("NTP DNS request failed\n");
        ntp_result(state, -1, NULL);
    }
}

static void ntp_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    NTP_T *state = (NTP_T*)arg;
    uint8_t mode = pbuf_get_at(p, 0) & 0x7;
    uint8_t stratum = pbuf_get_at(p, 1);

    if (ip_addr_cmp(addr, &state->ntp_server_address) && port == NTP_PORT && p->tot_len == NTP_MSG_LEN &&mode == 0x4 && stratum != 0)
    {
        uint8_t seconds_buf[4] = {0};
        pbuf_copy_partial(p, seconds_buf, sizeof(seconds_buf), 40);
        uint32_t seconds_since_1900 = seconds_buf[0] << 24 | seconds_buf[1] << 16 | seconds_buf[2] << 8 | seconds_buf[3];
        uint32_t seconds_since_1970 = seconds_since_1900 - NTP_DELTA;
        time_t epoch = seconds_since_1970;
        ntp_result(state, 0, &epoch);
    }
    else
    {
        printf("Invalid NTP response\n");
        ntp_result(state, -1, NULL);
    }
    pbuf_free(p);
}

static NTP_T* ntp_init(void)
{
    NTP_T *state = (NTP_T*)calloc(1, sizeof(NTP_T));
    if (!state)
    {
        printf("Failed to allocate state\n");
        return NULL;
    }
    state->ntp_pcb = udp_new_ip_type(IPADDR_TYPE_ANY);
    if (!state->ntp_pcb)
    {
        printf("Failed to create PCB\n");
        free(state);
        return NULL;
    }
    udp_recv(state->ntp_pcb, ntp_recv, state);
    return state;
}

void ntp_deinit(void)
{
    if (utc)
    {
        free((void*)utc);
        utc = NULL;
    }
}

void ntp_update_time(void)
{
    NTP_T *state = ntp_init();
    if (!state)
        return;
    if (absolute_time_diff_us(get_absolute_time(), state->ntp_test_time) < 0 && !state->dns_request_sent)
    {
        state->ntp_resend_alarm = add_alarm_in_ms(NTP_RESEND_TIME, ntp_failed_handler, state, true);
        cyw43_arch_lwip_begin();
        int err = dns_gethostbyname(NTP_SERVER, &state->ntp_server_address, ntp_dns_found, state);
        cyw43_arch_lwip_end();

        state->dns_request_sent = true;
        if (err == ERR_OK)
            ntp_request(state);
        else if (err != ERR_INPROGRESS)
        {
            printf("DNS request failed\n");
            ntp_result(state, -1, NULL);
        }
    }
    free(state);
}
