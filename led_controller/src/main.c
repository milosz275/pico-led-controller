#include "led_controller.h"

extern volatile bool stop_flag;

int main()
{
    enum init_result_t init_result = init();
    if (init_result != INIT_SUCCESS)
        return init_result;
    multicore_launch_core1(run_loop);
    while (true)
    {
        int wifi_link_status = cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA);
        if (wifi_link_status != CYW43_LINK_UP && wifi_link_status != CYW43_LINK_JOIN && !stop_flag)
        {
            printf("Wi-Fi link status: %d\n", wifi_link_status);
            BLINK_CODE_WIFI_DISCONNECTED;
            connect_to_wifi();
        }
        if (stop_flag)
            break;
        sleep_ms(25000);
    }
    printf("Stopping...\n");
    BLINK_CODE_SUCCESS_EXIT;
    cyw43_arch_deinit();
    ntp_deinit();
    return 0;
}
