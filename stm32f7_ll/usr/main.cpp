
#include "drivers.h"
#include "common.h"
#include "tmath.h"

#include "tft_display.h"

#include "image.h"

Terminal terminal;
Timer timer;    



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
    uart_init();

    terminal << "\n\nuart init done\n";
    

    timer.init();


    TFTDisplay display;
    display.init();

  
    Gpio<'B', 0, GPIO_MODE_OUT> led_1;
    Gpio<'B', 7, GPIO_MODE_OUT> led_2;
    Gpio<'B', 14, GPIO_MODE_OUT> led_3;
    

   

    uint32_t state = 0;

    float cx0 = -0.835f;
    float cy0 = -0.2321f;
    float cx1 = 0.0;
    float cy1 = -0.8;
    
    
    while (1)
    {
        uint32_t time_start = timer.get_time();

        

        state = (state+1)%32;

        float k = state/32.0f;
     

        float cx = (1.0f - k)*cx0 + k*cx1;
        float cy = (1.0f - k)*cy0 + k*cy1;

        fractal_demo(display, cx, cy); 
        
        uint32_t time_stop = timer.get_time();

        float fps = 1000.0f/(time_stop - time_start);

        terminal << "fps = " << fps << "\n";
    }
    
    
    
    return 0;
}
