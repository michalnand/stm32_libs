#include "drivers.h"


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            PLL_R                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */  
 void SystemClock_HSE_Config(void)
 {
    // Set FLASH latency 
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_7);
  
    // Enable PWR clock
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  
    // Enable HSE and wait for it to stabilize
    LL_RCC_HSE_Enable();
    while(LL_RCC_HSE_IsReady() != 1)
    {
    }
  
    // Activation OverDrive Mode
    LL_PWR_EnableOverDriveMode();
    while(LL_PWR_IsActiveFlag_OD() != 1)
    {
    }
  
    // Activation OverDrive Switching
    LL_PWR_EnableOverDriveSwitching();
    while(LL_PWR_IsActiveFlag_ODSW() != 1)
    {
    }
  
    // Main PLL configuration and activation using HSE
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 432, LL_RCC_PLLP_DIV_2);
    LL_RCC_PLL_Enable();
    while(LL_RCC_PLL_IsReady() != 1)
    {
    }
  
    // Sysclk activation on the main PLL
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
    {
    }
  
    // Set APB1 & APB2 prescalers
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  
    // Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function)
    SystemCoreClock = 216000000;
 }




/* ==============   BOARD SPECIFIC CONFIGURATION CODE BEGIN    ============== */
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 2
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 16
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            PLL_R                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
 
 void SystemClock_HSI_Config(void)
 {
   // Set FLASH latency 
   LL_FLASH_SetLatency(LL_FLASH_LATENCY_7);
 
   // Enable PWR clock
   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
 
   // Activation OverDrive Mode
   LL_PWR_EnableOverDriveMode();
   while(LL_PWR_IsActiveFlag_OD() != 1)
   {
   }; 
 
   // Activation OverDrive Switching
   LL_PWR_EnableOverDriveSwitching();
   while(LL_PWR_IsActiveFlag_ODSW() != 1)
   {
   };
   
   // Main PLL configuration and activation
   LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_16, 432, LL_RCC_PLLP_DIV_2);
   LL_RCC_PLL_Enable();
   while(LL_RCC_PLL_IsReady() != 1) 
   {
   };
   
   // Sysclk activation on the main PLL
   LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
   LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
   while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) 
   {
   }; 
   
   // Set APB1 & APB2 prescale
   LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
   LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
   
   // Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function)
   SystemCoreClock = 216000000; 
 }




void drivers_init()
{
    //SystemClock_HSE_Config();
    SystemClock_HSI_Config();
    
    // FPU init, Set CP10 and CP11 Full Access
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2)); 

    // Enable I-Cache
    SCB_EnableICache();

    // Enable D-Cache
    SCB_EnableDCache();
    
    LL_APB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_APB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    LL_APB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    LL_APB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
    LL_APB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
    LL_APB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
    LL_APB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
    LL_APB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
    LL_APB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOI);

    __enable_irq();
}

void delay_loops(uint32_t steps) 
{
    while (steps--)
    {
        __asm("nop");
    }
}

