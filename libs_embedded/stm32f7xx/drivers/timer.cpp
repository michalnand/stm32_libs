#include "timer.h"

#ifdef __cplusplus
extern "C" {
#endif

volatile uint32_t g_timer = 0;

void SysTick_Handler(void)
{
    g_timer++;
}


#ifdef __cplusplus
}
#endif


void Timer::init()
{
    g_timer = 0;

    // SysTick clock source = CPU clock (HCLK = 216 MHz)
    SysTick->CTRL = 0;  

    // Reload for 1 ms tick
    SysTick->LOAD = (SystemCoreClock / 1000) - 1;   // 1ms

    // Clear current value
    SysTick->VAL = 0;

    // Enable SysTick IRQ and SysTick timer
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |   // CPU clock
                    SysTick_CTRL_TICKINT_Msk   |   // Enable interrupt
                    SysTick_CTRL_ENABLE_Msk;       // Start SysTick
}


uint32_t Timer::get_time()
{
    return g_timer;
}


void Timer::delay_ms(uint32_t ms)
{
    uint32_t end = g_timer + ms;
    while (g_timer < end)
    {
        __asm__("nop");
    }
}
