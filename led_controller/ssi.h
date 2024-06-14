#ifndef _SSI_H
#define _SSI_H

#include <stdio.h>

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"

#include "light_state.h"
#include "blink.h"

const char* ssi_tags[] = {"volt","temp","gpio","led",NULL};

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
    case 3: // ws2812b led
        if (light_state)
            print_value = snprintf(pcInsert, iInsertLen, "ON");
        else
            print_value = snprintf(pcInsert, iInsertLen, "OFF");
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
