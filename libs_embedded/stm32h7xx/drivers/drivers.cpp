#include "drivers.h"

#include "stm32h7xx.h"
#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_pwr.h"
#include "stm32h7xx_ll_system.h"
#include "stm32h7xx_ll_utils.h"

/* ==============   STM32H7 HSI CLOCK CONFIGURATION    ============== */
/**
  * @brief  System Clock Configuration (HSI @ 480 MHz)
  *
  *            System Clock source            = PLL1 (HSI)
  *            SYSCLK(Hz)                     = 480000000
  *            HCLK(Hz)                       = 240000000
  *            AHB Prescaler                  = 2
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 2
  *            APB3 Prescaler                 = 2
  *            APB4 Prescaler                 = 2
  *            HSI Frequency(Hz)              = 64000000
  *            PLL1_M                         = 4
  *            PLL1_N                         = 240
  *            PLL1_P                         = 2
  *            VDD(V)                         = 3.3
  *            Regulator Voltage              = VOS0
  *            Flash Latency                  = 4 WS
  */
void SystemClock_HSI_ConfigAAA(void)
{
  /* Enable PWR clock */
  //LL_APB4_GRP2_EnableClock(LL_APB4_GRP2_PERIPH_PWR);

  //LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_EnableClock);
  //LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_PWR);
  //__HAL_RCC_PWR_CLK_ENABLE();




  /* Configure voltage scaling to VOS0 (required for 480 MHz) */
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE0);
  while (LL_PWR_IsActiveFlag_VOS() == 0)
  {
  }

  /* Enable HSI */
  LL_RCC_HSI_Enable();
  while (LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Configure Flash latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
  while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_4)
  {
  }

  /* Configure PLL1 */
  LL_RCC_PLL_SetSource(LL_RCC_PLLSOURCE_HSI);
  LL_RCC_PLL1_SetM(4);
  LL_RCC_PLL1_SetN(240);
  LL_RCC_PLL1_SetP(2);
  LL_RCC_PLL1_SetQ(4);
  LL_RCC_PLL1_SetR(2);

  LL_RCC_PLL1_Enable();
  LL_RCC_PLL1P_Enable();

  while (LL_RCC_PLL1_IsReady() != 1)
  {
  }

  /* Configure bus prescalers */
  LL_RCC_SetAHBPrescaler(LL_RCC_AHB_DIV_2);   /* 240 MHz */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  LL_RCC_SetAPB3Prescaler(LL_RCC_APB3_DIV_2);
  LL_RCC_SetAPB4Prescaler(LL_RCC_APB4_DIV_2);

  /* Switch system clock to PLL1 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL1);
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL1)
  {
  }

  /* Update CMSIS variable */
  SystemCoreClock = 480000000;
}



void SystemClock_Config(void)
{
    /*----------------------------------------------------------*/
    /* Power configuration                                      */
    /*----------------------------------------------------------*/

    /* Select LDO supply */
    LL_PWR_ConfigSupply(LL_PWR_LDO_SUPPLY);

    /* Voltage scaling to VOS0 (mandatory for 400 MHz) */
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE0);

    while (LL_PWR_IsActiveFlag_VOS() == 0);

    /*----------------------------------------------------------*/
    /* Enable HSI                                                */
    /*----------------------------------------------------------*/

    LL_RCC_HSI_Enable();
    while (LL_RCC_HSI_IsReady() == 0);

    /*----------------------------------------------------------*/
    /* Flash latency                                             */
    /*----------------------------------------------------------*/

    LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
    while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_4);

    /*----------------------------------------------------------*/
    /* PLL1 configuration                                        */
    /*----------------------------------------------------------*/

    /* Disable PLL1 before configuring */
    LL_RCC_PLL1_Disable();
    while (LL_RCC_PLL1_IsReady());

    /* Set PLL source */
    LL_RCC_PLL_SetSource(LL_RCC_PLLSOURCE_HSI);

    /*
     * HSI = 64 MHz
     * PLLM = 4  → 16 MHz
     * PLLN = 100 → 1600 MHz VCO
     * PLLP = 4  → 400 MHz SYSCLK
     */
    LL_RCC_PLL1_SetM(4);
    LL_RCC_PLL1_SetN(100);
    LL_RCC_PLL1_SetP(4);
    LL_RCC_PLL1_SetQ(8);
    LL_RCC_PLL1_SetR(8);

    LL_RCC_PLL1_SetVCOInputRange(LL_RCC_PLLINPUTRANGE_8_16);
    LL_RCC_PLL1_SetVCOOutputRange(LL_RCC_PLLVCORANGE_WIDE);

    /* Enable PLL1 */
    LL_RCC_PLL1_Enable();
    while (LL_RCC_PLL1_IsReady() == 0);

    /*----------------------------------------------------------*/
    /* Bus prescalers                                            */
    /*----------------------------------------------------------*/

    LL_RCC_SetSysPrescaler(LL_RCC_SYSCLK_DIV_1);   /* 400 MHz */
    LL_RCC_SetAHBPrescaler(LL_RCC_AHB_DIV_2);      /* 200 MHz */
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);    /* 100 MHz */
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);    /* 100 MHz */
    LL_RCC_SetAPB3Prescaler(LL_RCC_APB3_DIV_2);    /* 100 MHz */
    LL_RCC_SetAPB4Prescaler(LL_RCC_APB4_DIV_2);    /* 100 MHz */

    /*----------------------------------------------------------*/
    /* Switch SYSCLK                                             */
    /*----------------------------------------------------------*/

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL1);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL1);

    /* Update SystemCoreClock */
    SystemCoreClockUpdate();
}



void drivers_init()
{
    //SystemClock_HSE_Config();
    //SystemClock_HSI_Config();
    SystemClock_Config();
    
    // FPU init, Set CP10 and CP11 Full Access
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2)); 

    // Enable I-Cache
    SCB_EnableICache(); 

    // Enable D-Cache
    SCB_EnableDCache();




    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOD);
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOF);
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOH);
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOI);

    __enable_irq();

    NVIC_SetPriorityGrouping(3);  // preemption=4 bits, subpriority=0
}

void delay_loops(uint32_t steps) 
{
    while (steps--)
    {
        __asm("nop");
    }
}

