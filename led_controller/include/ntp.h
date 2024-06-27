#ifndef _NTP_H
#define _NTP_H

#include <string.h>
#include <time.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/dns.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"

#define NTP_SERVER "pool.ntp.org"
#define NTP_MSG_LEN 48
#define NTP_PORT 123
#define NTP_DELTA 2208988800
#define NTP_TEST_TIME (30 * 1000)
#define NTP_RESEND_TIME (10 * 1000)

/**
 * UTC time struct. Struct for the UTC time of program start.
 */
extern volatile struct tm *utc;

/**
 * UTC time struct. Struct for the last checked UTC time.
 */
extern volatile struct tm *current_utc;

/**
 * NTP struct. Struct for the NTP state.
 */
typedef struct NTP_T_
{
    ip_addr_t ntp_server_address;
    bool dns_request_sent;
    struct udp_pcb *ntp_pcb;
    absolute_time_t ntp_test_time;
    alarm_id_t ntp_resend_alarm;
} NTP_T;

/**
 * NTP result. Function handles the NTP result.
 * 
 * @param state: NTP state
 * @param status: status
 * @param result: result
 */
static void ntp_result(NTP_T* state, int status, time_t *result);

/**
 * NTP failed handler. Function handles the NTP failed handler.
 * 
 * @param id: alarm ID
 * @param user_data: user data
 * @return: time
 */
static int64_t ntp_failed_handler(alarm_id_t id, void *user_data);

/**
 * NTP request. Function sends the NTP request.
 * 
 * @param state: NTP state
 */
static void ntp_request(NTP_T *state);

/**
 * NTP DNS found. Function handles the NTP DNS found.
 * 
 * @param hostname: hostname
 * @param ipaddr: IP address
 * @param arg: argument
 */
static int64_t ntp_failed_handler(alarm_id_t id, void *user_data);

/**
 * NTP DNS found. Function handles the NTP DNS found.
 * 
 * @param hostname: hostname
 * @param ipaddr: IP address
 * @param arg: argument
 */
static void ntp_dns_found(const char *hostname, const ip_addr_t *ipaddr, void *arg);

/**
 * NTP recv. Function receives the NTP response.
 * 
 * @param arg: argument
 * @param pcb: UDP PCB
 * @param p: pbuf
 * @param addr: IP address
 * @param port: port
 */
static void ntp_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

/**
 * NTP init. Function initializes the NTP.
 * 
 * @return: NTP state
 */
static NTP_T* ntp_init(void);

/**
 * NTP deinit. Function de-initializes the NTP.
 */
void ntp_deinit(void);

/**
 * NTP update time. Function updates the NTP time.
 */
void ntp_update_time(void);

#endif
