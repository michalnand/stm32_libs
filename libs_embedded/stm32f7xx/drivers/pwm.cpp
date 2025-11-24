#include "pwm.h"



void pwm_init() 
{
     // Enable GPIO and timer clocks
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);

    // --- GPIO CONFIG for TIM4: PB6, PB7, PB8 (AF2) ---
    LL_GPIO_InitTypeDef gpio_init;
    gpio_init.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_init.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio_init.Pull = LL_GPIO_PULL_NO;
    gpio_init.Alternate = LL_GPIO_AF_2;



    gpio_init.Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_7 | LL_GPIO_PIN_8;
    LL_GPIO_Init(GPIOB, &gpio_init);

    // --- GPIO CONFIG for TIM8: PC6, PC7, PC8 (AF3) ---
    gpio_init.Alternate = LL_GPIO_AF_3;
    gpio_init.Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_7 | LL_GPIO_PIN_8;
    LL_GPIO_Init(GPIOC, &gpio_init);

    // --- TIM4 CONFIG ---
    LL_TIM_SetPrescaler(TIM4, 0);
    LL_TIM_SetAutoReload(TIM4, PWM_PERIOD - 1);
    LL_TIM_SetCounterMode(TIM4, LL_TIM_COUNTERMODE_UP);
    LL_TIM_EnableARRPreload(TIM4);

    LL_TIM_OC_SetMode(TIM4, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetMode(TIM4, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetMode(TIM4, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);

    LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH1);
    LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH2);
    LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH3);

    LL_TIM_OC_SetPolarity(TIM4, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH);
    LL_TIM_OC_SetPolarity(TIM4, LL_TIM_CHANNEL_CH2, LL_TIM_OCPOLARITY_HIGH);
    LL_TIM_OC_SetPolarity(TIM4, LL_TIM_CHANNEL_CH3, LL_TIM_OCPOLARITY_HIGH);

    LL_TIM_OC_SetCompareCH1(TIM4, 0);
    LL_TIM_OC_SetCompareCH2(TIM4, 0);
    LL_TIM_OC_SetCompareCH3(TIM4, 0);

    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2);
    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3);

    LL_TIM_EnableCounter(TIM4);

    // --- TIM8 CONFIG (Advanced Timer) ---
    LL_TIM_SetPrescaler(TIM8, 0);
    LL_TIM_SetAutoReload(TIM8, PWM_PERIOD - 1);
    LL_TIM_SetCounterMode(TIM8, LL_TIM_COUNTERMODE_UP);
    LL_TIM_EnableARRPreload(TIM8);

    LL_TIM_OC_SetMode(TIM8, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetMode(TIM8, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetMode(TIM8, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);

    LL_TIM_OC_EnablePreload(TIM8, LL_TIM_CHANNEL_CH1);
    LL_TIM_OC_EnablePreload(TIM8, LL_TIM_CHANNEL_CH2);
    LL_TIM_OC_EnablePreload(TIM8, LL_TIM_CHANNEL_CH3);

    LL_TIM_OC_SetPolarity(TIM8, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH);
    LL_TIM_OC_SetPolarity(TIM8, LL_TIM_CHANNEL_CH2, LL_TIM_OCPOLARITY_HIGH);
    LL_TIM_OC_SetPolarity(TIM8, LL_TIM_CHANNEL_CH3, LL_TIM_OCPOLARITY_HIGH);

    LL_TIM_OC_SetCompareCH1(TIM8, 0);
    LL_TIM_OC_SetCompareCH2(TIM8, 0);
    LL_TIM_OC_SetCompareCH3(TIM8, 0);

    LL_TIM_CC_EnableChannel(TIM8, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIM8, LL_TIM_CHANNEL_CH2);
    LL_TIM_CC_EnableChannel(TIM8, LL_TIM_CHANNEL_CH3);

    LL_TIM_EnableAllOutputs(TIM8); // Required for advanced timers
    LL_TIM_EnableCounter(TIM8);
}






void pwm_set(uint32_t t4ch1, uint32_t t4ch2, uint32_t t4ch3,
             uint32_t t8ch1, uint32_t t8ch2, uint32_t t8ch3)
{
    t4ch1 = (PWM_PERIOD * t4ch1) / PWM_MAX;
    t4ch2 = (PWM_PERIOD * t4ch2) / PWM_MAX;
    t4ch3 = (PWM_PERIOD * t4ch3) / PWM_MAX;
    
    t8ch1 = (PWM_PERIOD * t8ch1) / PWM_MAX;
    t8ch2 = (PWM_PERIOD * t8ch2) / PWM_MAX;
    t8ch3 = (PWM_PERIOD * t8ch3) / PWM_MAX;

    LL_TIM_OC_SetCompareCH1(TIM4, t4ch1);
    LL_TIM_OC_SetCompareCH2(TIM4, t4ch2);
    LL_TIM_OC_SetCompareCH3(TIM4, t4ch3);

    LL_TIM_OC_SetCompareCH1(TIM8, t8ch1);
    LL_TIM_OC_SetCompareCH2(TIM8, t8ch2);
    LL_TIM_OC_SetCompareCH3(TIM8, t8ch3);
}