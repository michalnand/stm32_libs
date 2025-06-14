#ifndef _TI2C_H_
#define _TI2C_H_

#include "i2c_interface.h"
#include "gpio.h"


#define NO_I2C_ACK 0
#define OK_I2C_ACK 1


#define SetHighSCL()  {scl = 1;}
#define SetLowSCL()   {scl = 0;}
 
#define SetHighSDA()  {sda.set_mode(GPIO_MODE_IN_FLOATING);}
#define SetLowSDA()   {sda = 0; sda.set_mode(GPIO_MODE_OUT);}

template<unsigned char port_name, uint16_t SDA_PIN, uint16_t SCL_PIN, int DELAY_CYCLES = 100>
class TI2C : public I2C_Interface
{   
    private:
        Gpio<port_name, SDA_PIN> sda;
        Gpio<port_name, SCL_PIN> scl;

        public:
        TI2C()
        {
    
        }
    
        virtual ~TI2C()
        {
    
        }
    
    
        void init()
        {
          sda.init();
          scl.init();
          sda = 0;
          scl = 0;
        }
    

     
        void start()
        {
          SetHighSCL();
          delay_long();

          SetHighSDA();
          delay_long();

          SetLowSDA(); 
          delay_long();

          SetLowSCL();
          delay_long();
        }
    
        void stop()
        {
          SetLowSCL();
          delay_long();

          SetLowSDA(); 
          delay_long();
          
          SetHighSCL();
          delay_long();

          SetHighSDA();
          delay_long();
        } 
    
    
        unsigned char write(unsigned char b)
        {
            unsigned char  i;
            unsigned char  return_ack;
    
            for (i = 0; i < 8; i++)
            {
                SetLowSCL();
                delay();
    
                if (b & (1<<7))
                {
                    SetHighSDA();
                }
                else
                {
                    SetLowSDA();
                }
    
                delay();
                SetHighSCL();
    
                delay();
                b <<= 1;
            }
            
            SetLowSCL();
            delay();
            SetHighSDA();
            delay();
    
            SetHighSCL();
            delay();
    
            if (sda)
                return_ack = NO_I2C_ACK;
            else
                return_ack = OK_I2C_ACK;
    
            SetLowSCL();
            delay();
    
            return(return_ack);
        }
    
    
        unsigned char read(unsigned char ack = 0)
        {
            unsigned char  i;
            unsigned char  c = 0x00;
    
            SetHighSDA();
            SetLowSCL();
            delay();
    
            for (i = 0; i < 8; i++)
            {
                c = c << 1;
                SetHighSCL();
                delay();
    
                if (sda)
                  c = c | 0x01;
    
                SetLowSCL();
                delay();
            }
    
    
              if(ack)
              {
                SetLowSDA();
              }
              else
              {
                SetHighSDA();
              }
    
            delay();
            SetHighSCL();
            delay();
            SetLowSCL();
            delay();
            SetHighSDA();
            delay();
    
            return (c);
        }
    
        void delay()
        {
          volatile uint32_t loops = DELAY_CYCLES;
          while (loops--)
          {
            
          }
        }

        void delay_long()
        {
          volatile uint32_t loops = 2*DELAY_CYCLES;
          while (loops--)
          {
            
          }
        }
    };    
#endif


