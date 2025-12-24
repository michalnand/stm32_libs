

#include "drivers.h"
#include "common.h"
#include "tft_display.h"
/*
#include "common.h"
#include "tmath.h"
*/

Terminal terminal;



void fractal_demo(TFTDisplay &display, float cx, float cy)
{
    uint32_t w = display.width();
    uint32_t h = display.height();

    // Julia constant
    //float cx = -0.7f;
    //float cy = 0.27015f;

    uint32_t max_iter = 40;

    display.set_full_screen();

    for (unsigned int y = 0; y < h; y++)
    {
        for (unsigned int x = 0; x < w; x++)
        {
            float zx = 1.5f*2.0f*(y*1.0f/h - 0.5f);
            float zy = 1.5f*2.0f*(x*1.0f/w - 0.5f);

            uint32_t i = 0; 
            while (zx * zx + zy * zy < 4.0f && i < max_iter)
            {
                float tmp = zx * zx - zy * zy + cx;
                zy = 2.0f * zx * zy + cy;
                zx = tmp;
                i++;
            }
            
            if (i >= max_iter)
            {
                i = 0;
            }   

            uint8_t r = (i*7)%256;
            uint8_t g = (i*3)%256;
            uint8_t b = (i*8)%256;

            display.set_pixel(r, g, b);
        }
    }

    display.end_full_screen();
}





int main() 
{      
    
    drivers_init();  

    Gpio<'A', 0, GPIO_MODE_OUT> led_0;
    led_0 = 1;

    Gpio<'A', 1, GPIO_MODE_OUT> led_1;
    led_1 = 1;

    uart_init();
    terminal.init();
    
    terminal << "uart init done\n";
     

    
    // display demo
    TFTDisplay display;
    display.init();
 

    uint32_t state = 0;

    float cx0 = -0.835f;
    float cy0 = -0.2321f;
    float cx1 = 0.0;
    float cy1 = -0.8;
    
    uint32_t cnt = 0;
    while (1)
    {
        if ((cnt%2) == 0)
            led_0 = 1;
        else
            led_0 = 0;

        //uint32_t time_start = timer.get_time();

        state = (state+1)%32;

        float k = state/32.0f;
     

        float cx = (1.0f - k)*cx0 + k*cx1;
        float cy = (1.0f - k)*cy0 + k*cy1;

        fractal_demo(display, cx, cy); 

        cnt++;
        
        //uint32_t time_stop = timer.get_time();

        //float fps = 1000.0f/(time_stop - time_start);

        //terminal << "fps = " << fps << "\n";
    }
    

    

    while (1)
    {
        led_0 = 1;
        led_1 = 1;
        delay_loops(10000000);

        terminal << "hello stm32h7\n";
        
        led_0 = 0;
        led_1 = 0;
        delay_loops(10000000);
    }

    
    return 0;
}
