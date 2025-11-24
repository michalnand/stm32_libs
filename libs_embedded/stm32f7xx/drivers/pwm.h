#ifndef _PWM_H_
#define _PWM_H_


#include "drivers.h"

    
// 20 kHz @ 108 MHz
#define PWM_PERIOD  ((uint32_t)5400)
#define PWM_MAX     ((uint32_t)1024)


/*
    init 6 PWM channels : 
    TIM4: PB6, PB7, PB8 
    TIM8: PC6, PC7, PC8 
*/
void pwm_init();

void pwm_set(uint32_t t4ch1, uint32_t t4ch2, uint32_t t4ch3,
             uint32_t t8ch1, uint32_t t8ch2, uint32_t t8ch3);


#endif