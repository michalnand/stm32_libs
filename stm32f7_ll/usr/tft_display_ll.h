#ifndef TFTDisplayLL_H_
#define TFTDisplayLL_H_

#include "drivers.h"

#include "stm32f7xx_ll_spi.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_bus.h"



class TFTDisplayLL
{
    public:
        void ll_init();
        uint8_t spib(uint8_t b);

    private:
        void spi_init();


    protected:    
        
        Gpio<'F', 13, GPIO_MODE_OUT> bl;     //backlight
        Gpio<'E', 9,  GPIO_MODE_OUT> cs;     //select
        Gpio<'E', 11, GPIO_MODE_OUT> dc;     //data/command
        Gpio<'F', 14, GPIO_MODE_OUT> reset;  //reset

        //Gpio<'E', 13, GPIO_MODE_OUT> mosi;   //data out
        //Gpio<'F', 15, GPIO_MODE_OUT> sck;    //clock

        Gpio<'A', 7, GPIO_MODE_OUT>         mosi;   // data out
        Gpio<'A', 6, GPIO_MODE_IN_PULLUP>   miso;   // data in
        Gpio<'A', 5, GPIO_MODE_OUT>         sck;    // clock
};

#endif