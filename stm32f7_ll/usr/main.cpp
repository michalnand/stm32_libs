//#include "drivers.h"
//#include "common.h"


#include "drivers.h"
#include "common.h"
#include "tmath.h"

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

#define MAT_N       ((uint32_t)100)
#define MAT_M       ((uint32_t)100)
#define MAT_K       ((uint32_t)100)

Matrix<int32_t, MAT_N, MAT_K> mat_a;
Matrix<int32_t, MAT_K, MAT_M> mat_b;
Matrix<int32_t, MAT_N, MAT_M> mat_c;

float matmul_test()
{
    // fill matrix A
    for (unsigned int i = 0; i < (MAT_N*MAT_K); i++)
    {
        float v = (get_random()%1000000)/1000000.0f;
        v = v*100.0f;
        if (get_random()%2)
        {
            v = -v;
        }

        mat_a[i] = v;
    }

    // fill matrix B
    for (unsigned int i = 0; i < (MAT_K*MAT_M); i++)
    {
        float v = (get_random()%1000000)/1000000.0f;
        v = v*100.0f;
        if (get_random()%2)
        {
            v = -v;
        }

        mat_b[i] = v;
    }

    uint32_t time_start = timer.get_time();

    mat_c = mat_a*mat_b;

    uint32_t time_stop = timer.get_time();

    uint32_t dt = time_stop - time_start;

    float macs = ((MAT_N*MAT_M*MAT_K)/(dt*0.001f));
    macs = macs/1000000.0f;
    return macs;
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

        float macs = matmul_test();

        terminal << "uptime = " << time << "\n";
        terminal << "pi  = " << pi << "\n";
        terminal << "macs  = " << macs << "\n";
        
        oled.put_info("uptime", time, 0);
        oled.put_info("pi", pi, 1);
        oled.put_info("macs", macs, 2);

        timer.delay_ms(500);
    }
    
    
    return 0;
}
