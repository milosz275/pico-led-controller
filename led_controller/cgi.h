#ifndef _CGI_H
#define _CGI_H

#include <stdio.h>

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"

#include "light_state.h"
#include "blink.h"

const char* cgi_onboard_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[])
{
    for (int i = 0; i < iNumParams; i++)
    {
        if (!strcmp(pcParam[i], "toggle"))
        {
            printf("Toggling onboard LED\n");
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, !cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN));
            break;
        }
        else if (!strcmp(pcParam[i], "on"))
        {
            printf("Turning onboard LED on\n");
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            break;
        }
        else if (!strcmp(pcParam[i], "off"))
        {
            printf("Turning onboard LED off\n");
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
            break;
        }
    }
    return "/index.shtml";
}

const char* cgi_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[])
{
    for (int i = 0; i < iNumParams; i++) {
        if (!strcmp(pcParam[i], "toggle"))
        {
            printf("Toggling LED strip\n");
            toggle_light_state();
            break;
        }
        else if (!strcmp(pcParam[i], "on"))
        {
            printf("Turning LED strip on\n");
            light_state = true;
            break;
        }
        else if (!strcmp(pcParam[i], "off"))
        {
            printf("Turning LED strip off\n");
            light_state = false;
            break;
        }
    }
    return "/index.shtml";
}

const char* cgi_favicon_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[])
{
    printf("Handling favicon request\n");
    return "/favicon.ico";
}

const char* cgi_manifests_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[])
{
    printf("Handling manifest request\n");
    return "/manifest.json";
}

const char* cgi_data_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[])
{
    printf("Handling data request\n");
    return "/data.shtml";
}

static const tCGI cgi_handlers[] =
{
    { "/onboard_led", cgi_onboard_led_handler },
    { "/led", cgi_led_handler },
    { "/favicon.ico", cgi_favicon_handler },
    { "/manifest.json", cgi_manifests_handler },
    { "/data.shtml", cgi_data_handler },
    { NULL, NULL }
};

void cgi_init()
{
    http_set_cgi_handlers(cgi_handlers, LWIP_ARRAYSIZE(cgi_handlers));
}

#endif
