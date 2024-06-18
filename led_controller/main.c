#include "led_controller.c"

int main()
{
    enum init_result_t init_result = init();
    if (init_result != INIT_SUCCESS)
        return init_result;
    multicore_launch_core1(run_loop);
    while (true)
        sleep_ms(500);
    BLINK_CODE_SUCCESS_EXIT;
    cyw43_arch_deinit();
    return 0;
}
