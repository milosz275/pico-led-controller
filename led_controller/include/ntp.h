#ifndef _NTP_H
#define _NTP_H

#include <string.h>
#include <time.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/dns.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"

extern volatile struct tm *utc;

typedef struct NTP_T_
{
    ip_addr_t ntp_server_address;
    bool dns_request_sent;
    struct udp_pcb *ntp_pcb;
    absolute_time_t ntp_test_time;
    alarm_id_t ntp_resend_alarm;
} NTP_T;

#define NTP_SERVER "pool.ntp.org"
#define NTP_MSG_LEN 48
#define NTP_PORT 123
#define NTP_DELTA 2208988800 // seconds between 1 Jan 1900 and 1 Jan 1970
#define NTP_TEST_TIME (30 * 1000)
#define NTP_RESEND_TIME (10 * 1000)
// #define TIMEZONE_OFFSET (+2 * 60 * 60)

static void ntp_result(NTP_T* state, int status, time_t *result);
static int64_t ntp_failed_handler(alarm_id_t id, void *user_data);
static void ntp_request(NTP_T *state);
static int64_t ntp_failed_handler(alarm_id_t id, void *user_data);
static void ntp_dns_found(const char *hostname, const ip_addr_t *ipaddr, void *arg);
static void ntp_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
static NTP_T* ntp_init(void);
void ntp_update_time(void);

#endif
