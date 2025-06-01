#include "drivers.h"


// set HSI for 64MHz
void SystemClock_Config_OLD(void)
{
    LL_RCC_HSI_Enable();
    while (!LL_RCC_HSI_IsReady())
    {
        __asm("nop");
    }

    // 2. Configure FLASH latency
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

    // 3. Set PLL config:
    // PLL source = HSI (16 MHz)
    // PLLM = 2
    // PLLN = 8
    // PLLR = 2  → 64 MHz output
    LL_RCC_PLL_ConfigDomain_SYS(
        LL_RCC_PLLSOURCE_HSI,   // PLL source
        LL_RCC_PLLM_DIV_2,      // Divider M = 2
        8,                      // Multiplier N = 8
        LL_RCC_PLLR_DIV_2       // Divider R = 2
    );

    // 4. Enable PLL
    LL_RCC_PLL_Enable();
    LL_RCC_PLL_EnableDomain_SYS();
    while (!LL_RCC_PLL_IsReady())
    {
        __asm("nop");
    }

    // 5. Set AHB and APB prescalers
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

    // 6. Select PLL as system clock source
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
    {
        __asm("nop");
    }

    // 7. Update SystemCoreClock variable
    SystemCoreClock = 64000000;
    SystemCoreClockUpdate();
}


// set HSI for 64MHz
void SystemClock_Config(void)
{
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
    while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
    {
        __asm("nop");
    }

    // HSI configuration and activation 
    LL_RCC_HSI_Enable();
    while(LL_RCC_HSI_IsReady() != 1)
    {
        __asm("nop");
    }

    // Main PLL configuration and activation 
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLR_DIV_2);
    LL_RCC_PLL_Enable();
    LL_RCC_PLL_EnableDomain_SYS();
    while(LL_RCC_PLL_IsReady() != 1)
    {
        __asm("nop");
    }

    // Set AHB prescaler
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

    // Sysclk activation on the main PLL 
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
    {
        __asm("nop");
    }

    // Set APB1 prescaler
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

    LL_Init1msTick(64000000);

    // Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) 
    LL_SetSystemCoreClock(64000000);
}


void drivers_init()
{
    // set HSI, 64MHz
    SystemClock_Config();

    // gpio clock init
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOF);

    __enable_irq();
}


void delay_loops(uint32_t steps) 
{
    while (steps--)
    {
        __asm("nop");
    }
}

