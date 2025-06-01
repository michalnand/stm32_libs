#include "drivers.h"
#include "common.h"
#include "tmath.h"

#include "os.h"

Terminal terminal;
Timer timer;

TI2C<TGPIOA, 0, 1> i2c;
SSD1315 oled;









#define MPU6050_ADDR    ((uint8_t)(0x68<<1))
#define PWR_MGMT_1      ((uint8_t)0x6b)
#define GYRO_XOUT_H     ((uint8_t)0x43)
#define GYRO_YOUT_H     ((uint8_t)0x45)
#define GYRO_ZOUT_H     ((uint8_t)0x47)



// Helper function to read 16-bit signed word (high + low byte)
int16_t read_word(unsigned char dev_adr, unsigned char reg_adr) 
{
    uint8_t high = i2c.read_reg(dev_adr, reg_adr);
    uint8_t low  = i2c.read_reg(dev_adr, reg_adr + 1);

    return (int16_t)((high << 8) | low);
}


volatile uint32_t task_1_sp[128];

void task_1()
{
    // mpu6050 turn on
    i2c.write_reg(MPU6050_ADDR, PWR_MGMT_1, 0x00);

    // meassure gyro offset
    int32_t gx_ofs = 0;
    int32_t gy_ofs = 0;
    int32_t gz_ofs = 0;
    for (unsigned int i = 0; i < 100; i++)
    {
        // read gyro
        int16_t gx = read_word(MPU6050_ADDR, GYRO_XOUT_H);
        int16_t gy = read_word(MPU6050_ADDR, GYRO_YOUT_H);
        int16_t gz = read_word(MPU6050_ADDR, GYRO_ZOUT_H);    

        gx_ofs+= gx;
        gy_ofs+= gy;
        gz_ofs+= gz;    

        timer.delay_ms(5);
    }

    gx_ofs/= 100;
    gy_ofs/= 100;
    gz_ofs/= 100;



    int32_t k      = 15;    
    int32_t gx_fil = 0;
    int32_t gy_fil = 0;
    int32_t gz_fil = 0;

    uint32_t steps = 0;

    while (1)
    {
        // read gyro
        int16_t gx = read_word(MPU6050_ADDR, GYRO_XOUT_H);
        int16_t gy = read_word(MPU6050_ADDR, GYRO_YOUT_H);
        int16_t gz = read_word(MPU6050_ADDR, GYRO_ZOUT_H);  
        
        gx = gx - gx_ofs;
        gy = gy - gy_ofs;   
        gz = gz - gz_ofs;

        // low pass filter
        gx_fil = (k*gx_fil + gx)/(k+1);
        gy_fil = (k*gy_fil + gy)/(k+1);
        gz_fil = (k*gz_fil + gz)/(k+1);

        // print result
        if ((steps%50) == 0)
        {
            terminal << gx_fil << " " << gy_fil << " " << gz_fil << "\n";

            oled.put_info("timer", timer.get_time()/1000, 0);
            oled.put_info("gx ", gx_fil, 1);
            oled.put_info("gy ", gy_fil, 2);
            oled.put_info("gz ", gz_fil, 3);          
        }

        steps++;
        timer.delay_ms(1);
        os_yield();
    }
}





volatile uint32_t task_2_sp[128];

void task_2()
{
    uint32_t steps = 0;

    pwm_init();

    while (1)
    {
        uint32_t r = sine_table[steps%SINE_TABLE_SIZE];
        uint32_t g = sine_table[(steps + SINE_TABLE_SIZE/3)%SINE_TABLE_SIZE];
        uint32_t b = sine_table[(steps + (2*SINE_TABLE_SIZE)/3)%SINE_TABLE_SIZE];

        uint32_t pwm_r = (r*PWM_MAX)/SINE_TABLE_MAX;
        uint32_t pwm_g = (g%SINE_TABLE_SIZE*PWM_MAX)/SINE_TABLE_MAX;
        uint32_t pwm_b = (b%SINE_TABLE_SIZE*PWM_MAX)/SINE_TABLE_MAX;

        pwm_set(pwm_r/5, pwm_g/5, pwm_b/5, 0);
       
        steps++;
        timer.delay_ms(5);
        os_yield();
    }
}

int main() 
{       
    
    drivers_init();   
    uart_init(); 


    //Terminal terminal;
    terminal << "\n\nuart init done\n";

    
    timer.init();
    i2c.init();
    oled.init(i2c);

    os_init();  


    os_add_task(task_1, (uint32_t*)task_1_sp, 128);
    os_add_task(task_2, (uint32_t*)task_2_sp, 128);    

    os_start();
  
    
    
    return 0;
}
