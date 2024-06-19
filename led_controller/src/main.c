#include "led_controller.h"

int main()
{
    enum init_result_t init_result = init();
    if (init_result != INIT_SUCCESS)
        return init_result;
    multicore_launch_core1(run_loop);
    while (true)
    {
        int wifi_link_status = cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA);
        if (wifi_link_status != CYW43_LINK_UP && wifi_link_status != CYW43_LINK_JOIN)
        {
            printf("Wi-Fi link status: %d\n", wifi_link_status);
            BLINK_CODE_WIFI_DISCONNECTED;
            connect_to_wifi();
        }
        sleep_ms(5000);
    }
        
    BLINK_CODE_SUCCESS_EXIT;
    cyw43_arch_deinit();
    return 0;
}
