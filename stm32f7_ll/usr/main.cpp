//#include "drivers.h"
//#include "common.h"
//#include "tmath.h"

#include "drivers.h"
#include "gpio.h"



int main() 
{        
    drivers_init();   

    //RCC->AHB1ENR|= RCC_AHB1ENR_GPIOBEN;

    /*
    GPIO_TypeDef *GPIOx = GPIOB;

    uint32_t pin = 2;

    //gpio speed 50MHz
    GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pin * 2));
    GPIOx->OSPEEDR |= ((uint32_t)(0x03) << (pin * 2));

    //push-pull output
    GPIOx->OTYPER &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pin));
    GPIOx->OTYPER |= (uint16_t)(((uint16_t)0x00) << ((uint16_t)pin));

    //pin as output
    GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pin * 2));
    GPIOx->MODER |= (((uint32_t)0x01) << (pin * 2));
    
    GPIOx->ODR|= (1<<pin); 
    */

    Gpio<'B', 2, GPIO_MODE_OUT> led;
    led = 1;      

    

    while (1)
    {
        led = 1;    
        delay_loops(100000);
        led = 0;
        delay_loops(10000000);
    }
    
    
    return 0;
}
