#ifndef _BLINK_CODES_H
#define _BLINK_CODES_H

#if !defined(DISABLE_BLINK_CODES)

#include "blink.h"

#define BLINK_CODE_GPIO_INIT_SUCCESS         do { onboard_led_blink(100, 900); onboard_led_blink(100, 100); } while(0)
#define BLINK_CODE_NETWORK_INIT_SUCCESS      do { onboard_led_blink(500, 500); onboard_led_blink(100, 100); } while(0)
#define BLINK_CODE_INIT_SUCCESS              do { onboard_led_blink(900, 100); onboard_led_blink(100, 100); } while(0)

#define BLINK_CODE_WIFI_CONNECTING           onboard_led_blink(100, 900);
#define BLINK_CODE_WIFI_CONNECTED            onboard_led_blink(200, 800);
#define BLINK_CODE_WIFI_FAILED               onboard_led_blink(500, 500);
#define BLINK_CODE_WIFI_DISCONNECTED         onboard_led_blink(900, 100);

#define BLINK_CODE_SSI_HANDLE                onboard_led_blink(20, 20);

#define BLINK_CODE_SUCCESS_EXIT              do { onboard_led_blink(100, 400); onboard_led_blink(100, 400); onboard_led_blink(100, 400); } while(0)

#endif
#endif
