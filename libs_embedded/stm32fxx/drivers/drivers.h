#ifndef _DRIVERS_H_
#define _DRIVERS_H_

#include <stdint.h>

#include "stm32g031xx.h"

#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_cortex.h"


#include "stm32g0xx_ll_bus.h"

#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_usart.h"

#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_i2c.h"
#include "stm32g0xx_ll_adc.h"


#include "gpio.h"
#include "i2c_interface.h"
#include "ti2c.h"
#include "uart.h"
#include "timer.h"
#include "pwm.h"


void drivers_init();

void delay_loops(uint32_t steps);


#endif