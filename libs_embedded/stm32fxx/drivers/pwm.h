#ifndef _PWM_H_
#define _PWM_H_


#include "drivers.h"

    
// 20 kHz @ 32 MHz
#define PWM_PERIOD  ((uint32_t)1600)

#define PWM_MAX     ((uint32_t)1024)

/*
    init timer 1 for PWM, 4 channels
        PA8     : ch1
        PA9     : ch2
        PA10    : ch3
        PA11    : ch4
    
    pwm max value is PWM_MAX
*/
void pwm_init();
void pwm_set(uint32_t ch1, uint32_t ch2, uint32_t ch3, uint32_t ch4);


#endif