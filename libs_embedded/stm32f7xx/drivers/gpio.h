#ifndef _GPIO_H_
#define _GPIO_H_


#define TGPIOA    ((unsigned char)0)
#define TGPIOB    ((unsigned char)1)
#define TGPIOC    ((unsigned char)2)
#define TGPIOD    ((unsigned char)3)
#define TGPIOE    ((unsigned char)4)
#define TGPIOF    ((unsigned char)5)
#define TGPIOG    ((unsigned char)6)
#define TGPIOH    ((unsigned char)7)
#define TGPIOI    ((unsigned char)8)
#define TGPIOJ    ((unsigned char)9)


#define GPIO_MODE_OUT             0       //push-pull output mode
#define GPIO_MODE_IN_FLOATING     1       //input mode
#define GPIO_MODE_IN_PULLUP       2       //input mode with pullup
#define GPIO_MODE_AN              4       //analog input
#define GPIO_MODE_AF              5       //alternate function
#define GPIO_MODE_OUT_OD          6       //open-drain output mode



constexpr GPIO_TypeDef* getGPIOPort(char portChar) 
{
    switch (portChar) 
    {
        #ifdef GPIOA
        case 'A': return GPIOA;
        #endif

        #ifdef GPIOB
        case 'B': return GPIOB;
        #endif

        #ifdef GPIOC
        case 'C': return GPIOC;
        #endif

        #ifdef GPIOD
        case 'D': return GPIOD;
        #endif

        #ifdef GPIOE
        case 'E': return GPIOE;
        #endif

        #ifdef GPIOF
        case 'F': return GPIOF;
        #endif

        #ifdef GPIOG
        case 'G': return GPIOG;
        #endif

        #ifdef GPIOH
        case 'H': return GPIOH;
        #endif

        #ifdef GPIOI
        case 'I': return GPIOI;
        #endif

        default: return nullptr;
    }
}

template <const unsigned char gpio, unsigned char pin, unsigned char mode = GPIO_MODE_OUT> 
class Gpio
{
  private:
    GPIO_TypeDef *GPIOx;

  public:
    Gpio()
    {
      init();
    }

    void init()
    {
      #ifdef GPIOA
      if (gpio == TGPIOA)
        GPIOx = GPIOA;
      #endif

      #ifdef GPIOB
      if (gpio == TGPIOB)
        GPIOx = GPIOB;
      #endif

      #ifdef GPIOC
      if (gpio == TGPIOC)
        GPIOx = GPIOC;
      #endif

      #ifdef GPIOD
      if (gpio == TGPIOD)
        GPIOx = GPIOD;
      #endif
 
      #ifdef GPIOE
      if (gpio == TGPIOE)
        GPIOx = GPIOE;
      #endif

      #ifdef GPIOF
      if (gpio == TGPIOF)
        GPIOx = GPIOF;
      #endif

      #ifdef GPIOG
      if (gpio == TGPIOG)
        GPIOx = GPIOG;
      #endif

      #ifdef GPIOH
      if (gpio == TGPIOH)
        GPIOx = GPIOH;
      #endif

      #ifdef GPIOI
      if (gpio == TGPIOI)
        GPIOx = GPIOI;
      #endif

      #ifdef GPIOJ
      if (gpio == TGPIOJ)
        GPIOx = GPIOJ;
      #endif 

      set_mode(mode);
    } 

    inline void set_mode(const unsigned char pin_mode)
       {
         if (pin_mode == GPIO_MODE_OUT)
         {
           //gpio speed 50MHz
           GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0 << (pin * 2));
           GPIOx->OSPEEDR |= ((uint32_t)(0x03) << (pin * 2));

           //push-pull output
           GPIOx->OTYPER &= ~((GPIO_OTYPER_OT0) << ((uint16_t)pin));
           GPIOx->OTYPER |= (uint16_t)(((uint16_t)0x00) << ((uint16_t)pin));

           //pin as output
           GPIOx->MODER  &= ~(GPIO_MODER_MODE0 << (pin * 2));
           GPIOx->MODER |= (((uint32_t)0x01) << (pin * 2));
         }

         //input mode, no pull-up
         if (pin_mode == GPIO_MODE_IN_FLOATING)
         {
           //gpio speed 50MHz
           GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0 << (pin * 2));
           GPIOx->OSPEEDR |= ((uint32_t)(0x03) << (pin * 2));

           //pin as output
           GPIOx->MODER  &= ~(GPIO_MODER_MODE0 << (pin * 2));
           GPIOx->MODER |= (((uint32_t)0x00) << (pin * 2));
         }

         //input mode, pull-up
         if (pin_mode == GPIO_MODE_IN_PULLUP)
         {
           //gpio speed 50MHz
           GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0 << (pin * 2));
           GPIOx->OSPEEDR |= ((uint32_t)(0x03) << (pin * 2));

           //pin as output
           GPIOx->MODER  &= ~(GPIO_MODER_MODE0 << (pin * 2));
           GPIOx->MODER |= (((uint32_t)0x00) << (pin * 2));

           //pullup enable
          
            uint32_t tmpreg = GPIOx->PUPDR;
            tmpreg &= ~(0x3 << (pin * 2));         // clear both PUPDR bits
            tmpreg |= (0x01 << (pin * 2));         // set pull-up
            GPIOx->PUPDR = tmpreg;
         }

         //alternate function
         if (pin_mode == GPIO_MODE_AF)
         {
           //gpio speed 50MHz
           GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0 << (pin * 2));
           GPIOx->OSPEEDR |= ((uint32_t)(0x03) << (pin * 2));

           //pin as output
           GPIOx->MODER  &= ~(GPIO_MODER_MODE0 << (pin * 2));
           GPIOx->MODER |= (((uint32_t)0x02) << (pin * 2));
         }

         //analog mode
         if (pin_mode == GPIO_MODE_AN)
         {
           //pin as output
           GPIOx->MODER  &= ~(GPIO_MODER_MODE0 << (pin * 2));
           GPIOx->MODER |= (((uint32_t)0x03) << (pin * 2));
         }


         if (pin_mode == GPIO_MODE_OUT_OD)
         {
           //gpio speed 50MHz
           GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0 << (pin * 2));
           GPIOx->OSPEEDR |= ((uint32_t)(0x03) << (pin * 2));

           //open drain output
           GPIOx->OTYPER &= ~((GPIO_OTYPER_OT0) << ((uint16_t)pin));
           GPIOx->OTYPER |= (uint16_t)(((uint16_t)0x01) << ((uint16_t)pin));

           //pin as output
           GPIOx->MODER  &= ~(GPIO_MODER_MODE0 << (pin * 2));
           GPIOx->MODER |= (((uint32_t)0x01) << (pin * 2));
         }
       }

       void set_af(unsigned char af)
       {
         uint32_t temp    = 0x00;
         uint32_t temp_2  = 0x00;

         temp = ((uint32_t)(af) << ((uint32_t)((uint32_t)pin & (uint32_t)0x07) * 4));
         GPIOx->AFR[pin >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)pin & (uint32_t)0x07) * 4));

         temp_2 = GPIOx->AFR[pin >> 0x03] | temp;
         GPIOx->AFR[pin >> 0x03] = temp_2;
       }

       Gpio& write(int value)
       {
         if (value)
             GPIOx->ODR|= (1<<pin);   //set pin to one
         else
             GPIOx->ODR&=~(1<<pin);   //set pin to zero

        return *this;
       }

       int read()
       {
         return (GPIOx->IDR&(1<<pin)) != 0;
       }

       Gpio& operator= (int value)
       {
         write(value); 
         return *this;
       }

       Gpio& operator= (Gpio& rhs)
       {
         return write(rhs.read());
       };

       void af_config(uint32_t af_config_mode)
       {
         uint32_t temp    = 0x00;
         uint32_t temp_2  = 0x00;

         temp = ((uint32_t)(af_config_mode) << ((uint32_t)((uint32_t)pin & (uint32_t)0x07) * 4));
         GPIOx->AFR[pin >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)pin & (uint32_t)0x07) * 4));
         temp_2 = GPIOx->AFR[pin >> 0x03] | temp;
         GPIOx->AFR[pin >> 0x03] = temp_2;
       }

       operator int()
       {
         return read();
       };

};


#endif
