#ifndef TFTDisplayLL_H_
#define TFTDisplayLL_H_

#include "drivers.h"

#include "stm32h7xx_ll_spi.h"
#include "stm32h7xx_ll_gpio.h"
#include "stm32h7xx_ll_bus.h"



class TFTDisplayLL
{
    public:
        void ll_init();
        uint8_t spib(uint8_t b);

    private:
        void spi_init();


    protected:    
        
        Gpio<'B', 10, GPIO_MODE_OUT> bl;     //backlight
        Gpio<'B', 11, GPIO_MODE_OUT> cs;     //select
        Gpio<'B', 12, GPIO_MODE_OUT> dc;     //data/command
        Gpio<'D', 8, GPIO_MODE_OUT> reset;   //reset


        Gpio<'B', 15, GPIO_MODE_OUT>         mosi;   // data out, MOSI, PB15
        Gpio<'B', 14, GPIO_MODE_IN_PULLUP>   miso;   // data in, MISO, PB14
        Gpio<'B', 13, GPIO_MODE_OUT>         sck;   // clock, SCK, PB13
};

#endif
