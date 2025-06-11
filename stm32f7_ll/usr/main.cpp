//#include "drivers.h"
//#include "common.h"
//#include "tmath.h"

#include "drivers.h"
#include "common.h"


Terminal terminal;
Timer timer;

TI2C<'C', 0, 3> i2c;
SSD1315 oled;


uint32_t g_random_val;

uint32_t get_random()
{
    g_random_val = (uint32_t)1103515245*g_random_val + 12345;
    return g_random_val;
}


float pi_test(uint32_t iterations)
{
    float pi = 0.0f;
    float sgn = 1.0f;

    for (float i = 0.0f; i < (float)iterations; i+= 1.0f)
    {
        pi+= sgn*1.0f/(2.0f*i + 1.0f);
        sgn = -sgn;
    }

    pi = pi*4.0f;

    return pi;
}

int main() 
{        
    drivers_init();  
    uart_init();

    terminal << "\n\nuart init done\n";
    

    timer.init();

  
    Gpio<'B', 0, GPIO_MODE_OUT> led_1;
    Gpio<'B', 7, GPIO_MODE_OUT> led_2;
    Gpio<'B', 14, GPIO_MODE_OUT> led_3;
    

    i2c.init();
    oled.init(i2c);
    

    while (1)
    {
        uint8_t v = (get_random() >> 8);

        if (v&(1<<0))
        {
            led_1 = 1;    
        }
        else
        {
            led_1 = 0;
        }

        if (v&(1<<1))
        {
            led_2 = 1;    
        }
        else
        {
            led_2 = 0;
        }

        if (v&(1<<2))
        {
            led_3 = 1;    
        }
        else
        {
            led_3 = 0;
        }
        
        uint32_t time = timer.get_time()/1000;

        uint32_t pi = pi_test(1000000)*100000000;

        terminal << "uptime = " << time << "\n";
        terminal << "pi  = " << pi << "\n";
        
        oled.put_info("uptime", time, 0);
        oled.put_info("pi", pi, 1);

        timer.delay_ms(500);
    }
    
    
    return 0;
}
