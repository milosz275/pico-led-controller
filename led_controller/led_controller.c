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
#include "blink.h"
#include "light_state.h"
#include "wifi_credentials.h"
#include "generated/ws2812.pio.h"

#include "lwipopts.h"
#include "lwip/apps/httpd.h"
#include "ssi.h"
#include "cgi.h"

#define WS2812_PIN 2
#define LIGHT_TOGGLE_PIN 15
#define IS_RGBW false

void connect_to_wifi()
{
    printf("Connecting to Wi-Fi...\n");
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000) != 0)
        printf("Attempting to connect...\n");
    printf("Connected!\n");
}

void button_irq_handler(uint gpio, uint32_t events)
{
    toggle_light_state(NUM_PIXELS);
}

bool init()
{
    stdio_init_all();
    gpio_init(LIGHT_TOGGLE_PIN);
    gpio_set_dir(LIGHT_TOGGLE_PIN, GPIO_IN);
    gpio_pull_up(LIGHT_TOGGLE_PIN);

    gpio_set_irq_enabled_with_callback(LIGHT_TOGGLE_PIN, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);

    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed");
        return false;
    }

    cyw43_arch_enable_sta_mode();
    connect_to_wifi();
    httpd_init();
    ssi_init(); 
    cgi_init();
    
    onboard_led_blink(250, 50);
    onboard_led_blink(250, 50);
    return true;
}

void apply_rainbow_effect(uint16_t* base_hue, uint8_t* speed_factor, uint8_t* density_factor, uint8_t* brightness)
{
    for (uint8_t i = 0; i < NUM_PIXELS; ++i)
    {
        uint16_t hue = (*base_hue + i * 360 / NUM_PIXELS * *density_factor) % 360;
        uint32_t color = hsv_to_rgb(hue * *brightness / 100, 255 * *brightness / 100, 255* *brightness / 100);
        put_pixel(color);
        hue++;
    }
    *speed_factor = rand() % 3 + 5; // 5, 6, 7
    *base_hue += *speed_factor;
    *base_hue %= 360;
}

int main()
{
    if (!init())
        return -1;
    printf("WS2812 LED Control, using pin %d\n", WS2812_PIN);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    puts("Beginning main loop");
    uint16_t base_hue = 0;
    uint8_t speed_factor = 4;
    uint8_t density_factor = 3;
    uint8_t brightness = 100;
    while (true)
    {
        if (light_state)
            apply_rainbow_effect(&base_hue, &speed_factor, &density_factor, &brightness);
        if (cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) != CYW43_LINK_UP)
        {
            turn_off_all(NUM_PIXELS);
            connect_to_wifi();
        }
        sleep_ms(70);
    }
    cyw43_arch_deinit();
}
