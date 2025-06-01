#ifndef _TIMER_H_
#define _TIMER_H_

#include "drivers.h"

class Timer
{
    public:
        void init();

    public:
        void callback();
        uint32_t get_time();
        void delay_ms(uint32_t ms_time);


    private:
        uint32_t timer_ticks;
};


#endif