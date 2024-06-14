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
            light_state.state = true;
            break;
        }
        else if (!strcmp(pcParam[i], "off"))
        {
            printf("Turning LED strip off\n");
            light_state.state = false;
            break;
        }
    }
    return "/index.shtml";
}

const char* cgi_led_mode_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[])
{
    for (int i = 0; i < iNumParams; i++) {
        if (!strcmp(pcParam[i], "rainbow-wheel"))
        {
            printf("Setting rainbow wheel mode\n");
            set_lighting_mode(MODE_RAINBOW_WHEEL);
            break;
        }
        else if (!strcmp(pcParam[i], "rainbow-cycle"))
        {
            printf("Setting rainbow cycle mode\n");
            set_lighting_mode(MODE_RAINBOW_CYCLE);
            break;
        }
        else if (!strcmp(pcParam[i], "red"))
        {
            printf("Setting red mode\n");
            set_lighting_mode(MODE_RED);
            break;
        }
        else if (!strcmp(pcParam[i], "green"))
        {
            printf("Setting green mode\n");
            set_lighting_mode(MODE_GREEN);
            break;
        }
        else if (!strcmp(pcParam[i], "blue"))
        {
            printf("Setting blue mode\n");
            set_lighting_mode(MODE_BLUE);
            break;
        }
        else if (!strcmp(pcParam[i], "cyan"))
        {
            printf("Setting cyan mode\n");
            set_lighting_mode(MODE_CYAN);
            break;
        }
        else if (!strcmp(pcParam[i], "yellow"))
        {
            printf("Setting yellow mode\n");
            set_lighting_mode(MODE_YELLOW);
            break;
        }
        else if (!strcmp(pcParam[i], "magenta"))
        {
            printf("Setting magenta mode\n");
            set_lighting_mode(MODE_MAGENTA);
            break;
        }
        else if (!strcmp(pcParam[i], "purple"))
        {
            printf("Setting purple mode\n");
            set_lighting_mode(MODE_PURPLE);
            break;
        }
        else if (!strcmp(pcParam[i], "pink"))
        {
            printf("Setting pink mode\n");
            set_lighting_mode(MODE_PINK);
            break;
        }
        else if (!strcmp(pcParam[i], "orange"))
        {
            printf("Setting orange mode\n");
            set_lighting_mode(MODE_ORANGE);
            break;
        }
        else if (!strcmp(pcParam[i], "turquoise"))
        {
            printf("Setting turquoise mode\n");
            set_lighting_mode(MODE_TURQUOISE);
            break;
        }
        else if (!strcmp(pcParam[i], "white"))
        {
            printf("Setting white mode\n");
            set_lighting_mode(MODE_WHITE);
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
    { "/mode", cgi_led_mode_handler },
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
