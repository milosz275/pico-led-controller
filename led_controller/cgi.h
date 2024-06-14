#ifndef _CGI_H
#define _CGI_H

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"

#include "light_state.h"
#include "blink.h"

const char* cgi_onboard_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[])
{
    if (!strcmp(pcParam[0] , "toggle"))
    {
        printf("Toggling onboard LED\n");
        if (cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN))
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        else
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    }
    return "/index.shtml";
}

const char* cgi_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[])
{
    if (!strcmp(pcParam[0] , "toggle"))
    {
        printf("Toggling LED strip\n");
        toggle_light_state();
    }
    return "/index.shtml";
}

const char* cgi_favicon_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[])
{
    printf("Favicon handling\n");
    return "/favicon.ico";
}

const char* cgi_manifests_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[])
{
    printf("Manifest handling\n");
    return "/manifest.json";
}

static const tCGI cgi_handlers[] =
{
    {
        "/onboard_led.cgi", cgi_onboard_led_handler
    },
    {
        "/led.cgi", cgi_led_handler
    },
    {
        "/favicon.ico", cgi_favicon_handler
    },
    {
        "/manifest.json", cgi_manifests_handler
    },
};

void cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers, 4);
}

#endif
