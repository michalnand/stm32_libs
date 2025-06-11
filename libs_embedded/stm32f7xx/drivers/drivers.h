#ifndef _DRIVERS_H_
#define _DRIVERS_H_

#include "stm32f7xx.h"
#include "stm32f7xx_ll_adc.h"
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_cortex.h"
#include "stm32f7xx_ll_crc.h"
#include "stm32f7xx_ll_dac.h"
#include "stm32f7xx_ll_dma.h"
#include "stm32f7xx_ll_dma2d.h"
#include "stm32f7xx_ll_exti.h"
#include "stm32f7xx_ll_fmc.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_i2c.h"
#include "stm32f7xx_ll_iwdg.h"
#include "stm32f7xx_ll_lptim.h"
#include "stm32f7xx_ll_pwr.h"
#include "stm32f7xx_ll_rcc.h"
#include "stm32f7xx_ll_rtc.h"
#include "stm32f7xx_ll_tim.h"
#include "stm32f7xx_ll_usart.h"


#include "stm32f7xx_ll_system.h"


#include "gpio.h"
#include "uart.h"
#include "timer.h"
#include "ti2c.h"

void drivers_init();   
void delay_loops(uint32_t steps);

#endif