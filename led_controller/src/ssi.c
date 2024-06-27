#include "ssi.h"

#include <stdio.h>

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"

#include "ntp.h"
#include "light_state.h"
#include "blink.h"

static const char* ssi_tags[] =
{
    "volt",
    "temp",
    "gpio",
    "led",
    "mode",
    "color",
    "bright",
    "tm",
    NULL
};

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
        switch (light_state.light_mode)
        {
        case MODE_RAINBOW_WHEEL:
            print_value = snprintf(pcInsert, iInsertLen, "rainbow-wheel");
            break;
        case MODE_RAINBOW_CYCLE:
            print_value = snprintf(pcInsert, iInsertLen, "rainbow-cycle");
            break;
        case MODE_STATIC:
            print_value = snprintf(pcInsert, iInsertLen, "static");
            break;
        case MODE_BREATHING:
            print_value = snprintf(pcInsert, iInsertLen, "breathing");
            break;
        case MODE_FLASHING:
            print_value = snprintf(pcInsert, iInsertLen, "flashing");
            break;
        case MODE_LOADING:
            print_value = snprintf(pcInsert, iInsertLen, "loading");
            break;
        case MODE_WAVE:
            print_value = snprintf(pcInsert, iInsertLen, "wave");
            break;
        case MODE_FADE:
            print_value = snprintf(pcInsert, iInsertLen, "fade");
            break;
        default:
            print_value = 0;
            break;
        }
        break;
    case 5: // light color
        switch (light_state.color)
        {
        case COLOR_RED:
            print_value = snprintf(pcInsert, iInsertLen, "red");
            break;
        case COLOR_GREEN:
            print_value = snprintf(pcInsert, iInsertLen, "green");
            break;
        case COLOR_BLUE:
            print_value = snprintf(pcInsert, iInsertLen, "blue");
            break;
        case COLOR_WHITE:
            print_value = snprintf(pcInsert, iInsertLen, "white");
            break;
        case COLOR_PURPLE:
            print_value = snprintf(pcInsert, iInsertLen, "purple");
            break;
        case COLOR_YELLOW:
            print_value = snprintf(pcInsert, iInsertLen, "yellow");
            break;
        case COLOR_CYAN:
            print_value = snprintf(pcInsert, iInsertLen, "cyan");
            break;
        case COLOR_ORANGE:
            print_value = snprintf(pcInsert, iInsertLen, "orange");
            break;
        case COLOR_PINK:
            print_value = snprintf(pcInsert, iInsertLen, "pink");
            break;
        case COLOR_TURQUOISE:
            print_value = snprintf(pcInsert, iInsertLen, "turquoise");
            break;
        case COLOR_MAGENTA:
            print_value = snprintf(pcInsert, iInsertLen, "magenta");
            break;
        default:
            print_value = 0;
            break;
        }
        break;
    case 6: // brightness
        print_value = snprintf(pcInsert, iInsertLen, "%d", (int)(light_state.brightness / 255.0 * 100.0));
        break;
    case 7: // time tm
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
