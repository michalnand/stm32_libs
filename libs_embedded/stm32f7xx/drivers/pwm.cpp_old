#include "pwm.h"



void pwm_init() 
{
    // Enable TIM1 and GPIOA clocks
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

    // PA8-PA11 → TIM1_CH1–CH4 (AF2)
    for (int pin = 8; pin <= 11; pin++) {
        LL_GPIO_SetPinMode(GPIOA, 1 << pin, LL_GPIO_MODE_ALTERNATE);
        LL_GPIO_SetPinSpeed(GPIOA, 1 << pin, LL_GPIO_SPEED_FREQ_HIGH);
        LL_GPIO_SetPinOutputType(GPIOA, 1 << pin, LL_GPIO_OUTPUT_PUSHPULL);
        LL_GPIO_SetAFPin_8_15(GPIOA, 1 << pin, LL_GPIO_AF_2);
    }

    // Set TIM1 prescaler and auto-reload
    LL_TIM_SetPrescaler(TIM1, 0);
    LL_TIM_SetAutoReload(TIM1, PWM_PERIOD - 1);
    LL_TIM_SetCounterMode(TIM1, LL_TIM_COUNTERMODE_UP);
    LL_TIM_EnableARRPreload(TIM1);

    // Configure CH1–CH4 in PWM1 mode
    LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH4, LL_TIM_OCMODE_PWM1);

    // Enable preload and polarity for each channel
    LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH1);
    LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH2);
    LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH3);
    LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH4);

    LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH);
    LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH2, LL_TIM_OCPOLARITY_HIGH);
    LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH3, LL_TIM_OCPOLARITY_HIGH);
    LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH4, LL_TIM_OCPOLARITY_HIGH);

    // Set duty cycles to 0
    LL_TIM_OC_SetCompareCH1(TIM1, 0);
    LL_TIM_OC_SetCompareCH2(TIM1, 0);
    LL_TIM_OC_SetCompareCH3(TIM1, 0);
    LL_TIM_OC_SetCompareCH4(TIM1, 0);

    // Enable output channels
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH2);
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH3);
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH4);

    // Enable main output (advanced timer requirement!)
    LL_TIM_EnableAllOutputs(TIM1);

    // Enable counter
    LL_TIM_EnableCounter(TIM1);
}




void pwm_set(uint32_t ch1, uint32_t ch2, uint32_t ch3, uint32_t ch4)
{
    ch1 = (PWM_PERIOD*ch1)/PWM_MAX;
    ch2 = (PWM_PERIOD*ch2)/PWM_MAX; 
    ch3 = (PWM_PERIOD*ch3)/PWM_MAX;    
    ch4 = (PWM_PERIOD*ch4)/PWM_MAX;

    LL_TIM_OC_SetCompareCH1(TIM1, ch1);
    LL_TIM_OC_SetCompareCH2(TIM1, ch2);
    LL_TIM_OC_SetCompareCH3(TIM1, ch3);
    LL_TIM_OC_SetCompareCH4(TIM1, ch4);
}
