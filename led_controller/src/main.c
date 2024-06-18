#include "led_controller.h"

int main()
{
    enum init_result_t init_result = init();
    if (init_result != INIT_SUCCESS)
        return init_result;
    multicore_launch_core1(run_loop);
    while (true)
    {
        if (cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) != CYW43_LINK_UP)
        {
            BLINK_CODE_WIFI_DISCONNECTED;
            turn_off_all(NUM_PIXELS);
            connect_to_wifi();
        }
        sleep_ms(5000);
    }
        
    BLINK_CODE_SUCCESS_EXIT;
    cyw43_arch_deinit();
    return 0;
}
