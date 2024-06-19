#include "led_controller.h"

#include <stdio.h>
#include <stdlib.h>

#include "urgb.h"
#include "hsv.h"
#include "ws2812b.h"
#include "light_state.h"
#include "wifi_credentials.h"
#include "generated/ws2812.pio.h"

#include "lwipopts.h"
#include "lwip/apps/httpd.h"
#include "ssi.h"
#include "cgi.h"
#include "ntp.h"

volatile bool light_state_toggle_request = false;
volatile bool light_mode_toggle_request = false;
volatile bool stop_flag = false;
volatile uint64_t last_press_time = 0;

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
    uint64_t current_time = time_us_64();
    if (current_time - last_press_time >= DEBOUNCE_TIME_US)
    {
        last_press_time = current_time;
        switch (gpio)
        {
        case LIGHT_TOGGLE_PIN:
            light_state_toggle_request = true;
            break;
        case MODE_BUTTON_PIN:
            light_mode_toggle_request = true;
            break;
        case STOP_BUTTON_PIN:
            stop_flag = true;
            break;
        default:
            break;
        }
    }
}

enum init_result_t init()
{
    if (!stdio_init_all())
    {
        printf("Stdio init failed");
        return STDIO_INIT_FAILURE;
    }

    // GPIO setup - LED
    gpio_init(CYW43_WL_GPIO_LED_PIN);
    gpio_set_dir(CYW43_WL_GPIO_LED_PIN, GPIO_OUT);
    gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

    // GPIO setup - buttons
    gpio_init(LIGHT_TOGGLE_PIN);
    gpio_set_dir(LIGHT_TOGGLE_PIN, GPIO_IN);
    gpio_pull_up(LIGHT_TOGGLE_PIN);

    gpio_init(MODE_BUTTON_PIN);
    gpio_set_dir(MODE_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(MODE_BUTTON_PIN);

    gpio_init(STOP_BUTTON_PIN);
    gpio_set_dir(STOP_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(STOP_BUTTON_PIN);

    // GPIO setup - interrupts
    gpio_set_irq_enabled_with_callback(LIGHT_TOGGLE_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_button_irq_handler);
    gpio_set_irq_enabled_with_callback(MODE_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_button_irq_handler);
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
    ntp_update_time();
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

void shuffle_modes()
{
    sleep_ms(5000);
    light_state.lighting_mode = (light_state.lighting_mode + 1) % NUM_LIGHTING_MODES;
}

void run_loop()
{
    uint16_t base_hue = 0;
    uint8_t speed_factor_wheel = 4;
    uint8_t speed_factor_cycle = 1;
    uint8_t density_factor = 3;
    while (true)
    {
        if (light_state_toggle_request)
        {
            toggle_light_state(NUM_PIXELS);
            light_state_toggle_request = false;
        }
        if (light_mode_toggle_request)
        {
            toggle_light_mode();
            light_mode_toggle_request = false;
        }
        if (stop_flag)
        {
            turn_off_all(NUM_PIXELS);
            break;
        }
        switch (light_state.lighting_mode)
        {
        case MODE_RAINBOW_WHEEL:
            if (light_state.state)
                apply_rainbow_wheel_effect(NUM_PIXELS, &base_hue, &speed_factor_wheel, &density_factor);
            break;
        case MODE_RAINBOW_CYCLE:
            if (light_state.state)
                apply_rainbow_cycle_effect(NUM_PIXELS, &base_hue, &speed_factor_cycle);
            break;
        default:
            break;
        }
        sleep_ms(50);
    }
}