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

    // Enable TIM2 clock
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

    // Set prescaler and ARR for 1ms interrupt  
    LL_TIM_SetPrescaler(TIM2, 64 - 1);         // 64 MHz / 64 = 1 MHz
    LL_TIM_SetAutoReload(TIM2, 1000 - 1);      // 1 MHz / 1000 = 1 kHz = 1 ms
    LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);
    LL_TIM_EnableARRPreload(TIM2);

    // Enable update interrupt
    LL_TIM_EnableIT_UPDATE(TIM2);

    // Enable TIM2 NVIC interrupt
    NVIC_SetPriority(TIM2_IRQn, 0);
    NVIC_EnableIRQ(TIM2_IRQn);

    // Enable counter
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

