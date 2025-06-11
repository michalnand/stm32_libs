#include "timer.h"



#ifdef __cplusplus
extern "C" {
#endif

volatile uint32_t g_timer;

void TIM2_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM2))
    {
        LL_TIM_ClearFlag_UPDATE(TIM2);
        g_timer++;
    }
}

#ifdef __cplusplus
}
#endif


void Timer::init()
{
    g_timer = 0;

    // Enable TIM2 clock (APB1 group)
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

    // Timer input clock is typically APB1 * 2 = 108 MHz (on F746, if APB1 prescaler != 1)
    // For portability, use SystemCoreClock and adjust prescaler
    uint32_t timer_clk = SystemCoreClock / 1; // Assume APB1 prescaler = 1 (check RCC config!)
    LL_TIM_SetPrescaler(TIM2, (timer_clk / 1000000) - 1);   // 1 MHz timer clock
    LL_TIM_SetAutoReload(TIM2, 1000 - 1);                   // 1ms period (1000 ticks at 1 MHz)
    LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);
    LL_TIM_EnableARRPreload(TIM2);

    // Enable update interrupt
    LL_TIM_EnableIT_UPDATE(TIM2);

    // Configure NVIC
    NVIC_SetPriority(TIM2_IRQn, 0);
    NVIC_EnableIRQ(TIM2_IRQn);

    // Start counter
    LL_TIM_EnableCounter(TIM2);
}

    
uint32_t Timer::get_time()
{
    return g_timer;
}   


void Timer::delay_ms(uint32_t ms_time)
{
    uint32_t time_end = get_time() + ms_time;

    while (get_time() < time_end)
    {
        __asm("nop");
    }
}

