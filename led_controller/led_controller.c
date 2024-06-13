#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <boards/pico_w.h>
#include <hardware/pio.h>
#include <hardware/clocks.h>

#include "urgb.h"
#include "hsv.h"
#include "ws2812b.h"
#include "wifi_credentials.h"
#include "generated/ws2812.pio.h"

#include "lwipopts.h"
// #include "lwip/apps/httpd.h"
// #include "ssi.h"
// #include "cgi.h"

#define LIGHT_TOGGLE_PIN 1
#define WS2812_PIN 2
#define NUM_PIXELS 118
#define IS_RGBW false

bool light_on = true;
bool button_pressed_prev = true;

void onboard_led_blink(int on_time, int off_time)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(on_time);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(off_time);
}

bool init()
{
    stdio_init_all();
    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed");
        return false;
    }

    cyw43_arch_enable_sta_mode();
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000) != 0) // ten seconds timeout
        printf("Attempting to connect...\n");
    printf("Connected!\n");
    onboard_led_blink(250, 50);
    onboard_led_blink(250, 0);
    return true;
}

void apply_rainbow_effect(int *base_hue, int *speed_factor, int *density_factor, int *brightness)
{
    for (int i = 0; i < NUM_PIXELS; ++i)
    {
        int hue = (*base_hue + i * 360 / NUM_PIXELS * *density_factor) % 360;
        uint32_t color = hsv_to_rgb(hue * *brightness / 100, 255 * *brightness / 100, 255* *brightness / 100);
        put_pixel(color);
        hue++;
    }
    *speed_factor = rand() % 3 + 5;
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
    int base_hue = 0;
    int speed_factor = 5;
    int density_factor = 2;
    int brightness = 100;
    while (true)
    {
        onboard_led_blink(50, 10);
        apply_rainbow_effect(&base_hue, &speed_factor, &density_factor, &brightness);
    }
}
