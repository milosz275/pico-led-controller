#ifndef _SSI_H
#define _SSI_H

#include <stdio.h>

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"

#include "light_state.h"
#include "blink.h"
#include "ntp.h"

const char* ssi_tags[] = {"volt","temp","gpio","led","mode","tm",NULL};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen)
{
    size_t print_value;
    switch (iIndex)
    {
    case 0: // volt
        print_value = snprintf(pcInsert, iInsertLen, "%f", (adc_read() * 3.3f / (1 << 12)));
        break;
    case 1: // temp
        print_value = snprintf(pcInsert, iInsertLen, "%f", (27.0f - ((adc_read() * 3.3f / (1 << 12)) - 0.706f) / 0.001721f));
        break;
    case 2: // gpio led
        if (cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN))
            print_value = snprintf(pcInsert, iInsertLen, "ON");
        else
            print_value = snprintf(pcInsert, iInsertLen, "OFF");
        break;
    case 3: // light state
        if (light_state.state)
            print_value = snprintf(pcInsert, iInsertLen, "ON");
        else
            print_value = snprintf(pcInsert, iInsertLen, "OFF");
        break;
    case 4: // light mode
        switch (light_state.lighting_mode)
        {
        case MODE_RAINBOW_WHEEL:
            print_value = snprintf(pcInsert, iInsertLen, "rainbow-wheel");
            break;
        case MODE_RAINBOW_CYCLE:
            print_value = snprintf(pcInsert, iInsertLen, "rainbow-cycle");
            break;
        case MODE_RED:
            print_value = snprintf(pcInsert, iInsertLen, "red");
            break;
        case MODE_GREEN:
            print_value = snprintf(pcInsert, iInsertLen, "green");
            break;
        case MODE_BLUE:
            print_value = snprintf(pcInsert, iInsertLen, "blue");
            break;
        case MODE_WHITE:
            print_value = snprintf(pcInsert, iInsertLen, "white");
            break;
        case MODE_PURPLE:
            print_value = snprintf(pcInsert, iInsertLen, "purple");
            break;
        case MODE_YELLOW:
            print_value = snprintf(pcInsert, iInsertLen, "yellow");
            break;
        case MODE_CYAN:
            print_value = snprintf(pcInsert, iInsertLen, "cyan");
            break;
        case MODE_ORANGE:
            print_value = snprintf(pcInsert, iInsertLen, "orange");
            break;
        case MODE_PINK:
            print_value = snprintf(pcInsert, iInsertLen, "pink");
            break;
        case MODE_TURQUOISE:
            print_value = snprintf(pcInsert, iInsertLen, "turquoise");
            break;
        case MODE_MAGENTA:
            print_value = snprintf(pcInsert, iInsertLen, "magenta");
            break;
        default:
            print_value = 0;
            break;
        }
        break;
    case 5: // time tm
        if (utc)
            print_value = snprintf(pcInsert, iInsertLen, "%04d-%02d-%02dT%02d:%02d:%02dZ", utc->tm_year + 1900, utc->tm_mon + 1, utc->tm_mday, utc->tm_hour, utc->tm_min, utc->tm_sec);
        else
            print_value = snprintf(pcInsert, iInsertLen, "NULL");
        break;
    default:
        print_value = 0;
        break;
    }
    return (u16_t)print_value;
}

void ssi_init()
{
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}

#endif
