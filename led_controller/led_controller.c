#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <boards/pico_w.h>
#include <hardware/pio.h>
#include <hardware/gpio.h>
#include <hardware/clocks.h>

#include "urgb.h"
#include "hsv.h"
#include "ws2812b.h"
#include "blink_codes.h"
#include "light_state.h"
#include "wifi_credentials.h"
#include "generated/ws2812.pio.h"

#include "lwipopts.h"
#include "lwip/apps/httpd.h"
#include "ssi.h"
#include "cgi.h"

#define WS2812_PIN 2
#define LIGHT_TOGGLE_PIN 15
#define STOP_BUTTON_PIN 17
#define IS_RGBW false

volatile bool stop_flag = false;

void connect_to_wifi()
{
    BLINK_CODE_WIFI_CONNECTING;
    printf("Connecting to Wi-Fi...\n");
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000) != 0)
        printf("Attempting to connect...\n");
    printf("Connected!\n");
    BLINK_CODE_WIFI_CONNECTED;
}

void gpio_button_irq_handler(uint gpio, uint32_t events)
{
    switch (gpio)
    {
    case LIGHT_TOGGLE_PIN:
        toggle_light_state(NUM_PIXELS);
        break;
    case STOP_BUTTON_PIN:
        stop_flag = true;
        break;
    default:
        break;
    }
}

enum init_result_t
{
    INIT_SUCCESS,
    STDIO_INIT_FAILURE,
    WIFI_INIT_FAILURE
};

enum init_result_t init()
{
    if (!stdio_init_all())
    {
        printf("Stdio init failed");
        return STDIO_INIT_FAILURE;
    }

    // GPIO setup - buttons
    gpio_init(CYW43_WL_GPIO_LED_PIN);
    gpio_set_dir(CYW43_WL_GPIO_LED_PIN, GPIO_OUT);
    gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

    gpio_init(LIGHT_TOGGLE_PIN);
    gpio_set_dir(LIGHT_TOGGLE_PIN, GPIO_IN);
    gpio_pull_up(LIGHT_TOGGLE_PIN);

    gpio_init(STOP_BUTTON_PIN);
    gpio_set_dir(STOP_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(STOP_BUTTON_PIN);

    // GPIO setup - interrupts
    gpio_set_irq_enabled_with_callback(LIGHT_TOGGLE_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_button_irq_handler);
    gpio_set_irq_enabled_with_callback(STOP_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_button_irq_handler);

    // Wi-Fi setup
    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed");
        return WIFI_INIT_FAILURE;
    }
    cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));
    cyw43_arch_enable_sta_mode();
    connect_to_wifi();
    httpd_init();
    ssi_init(); 
    cgi_init();
    BLINK_CODE_NETWORK_INIT_SUCCESS;

    // PIO setup - WS2812B
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
    printf("WS2812 LED Control, using pin %d\n", WS2812_PIN);

    BLINK_CODE_INIT_SUCCESS;
    return INIT_SUCCESS;
}

void apply_rainbow_effect(uint16_t* base_hue, uint8_t* speed_factor, uint8_t* density_factor)
{
    for (uint8_t i = 0; i < NUM_PIXELS; ++i)
    {
        uint16_t hue = (*base_hue + i * 360 / NUM_PIXELS * *density_factor) % 360;
        uint32_t color = hsv_to_rgb(hue, 255, 255);
        put_pixel(color);
        hue++;
    }
    *speed_factor = rand() % 3 + 5; // 5, 6, 7
    *base_hue += *speed_factor;
    *base_hue %= 360;
}

int main()
{
    enum init_result_t init_result = init();
    if (init_result != INIT_SUCCESS)
        return init_result;

    puts("Beginning main loop");
    uint16_t base_hue = 0;
    uint8_t speed_factor = 4;
    uint8_t density_factor = 3;
    while (true)
    {
        if (stop_flag)
        {
            turn_off_all(NUM_PIXELS);
            break;
        }
        if (light_state)
            apply_rainbow_effect(&base_hue, &speed_factor, &density_factor);
        if (cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) != CYW43_LINK_UP)
        {
            BLINK_CODE_WIFI_DISCONNECTED;
            turn_off_all(NUM_PIXELS);
            connect_to_wifi();
        }
        sleep_ms(40);
    }
    BLINK_CODE_SUCCESS_EXIT;
    cyw43_arch_deinit();
    return 0;
}
