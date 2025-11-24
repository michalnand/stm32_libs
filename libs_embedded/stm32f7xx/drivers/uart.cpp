#include "uart.h"

#include "drivers.h"

/*
void uart_init()
{
    // 1. Enable GPIOD and USART3 clocks
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);

    // 2. Set USART3 clock source (if required; STM32F7 usually defaults to PCLK1)
    // No need to call LL_RCC_SetUSARTClockSource for F7 unless you're changing the source

    // 3. Configure PD8 and PD9 as Alternate Function 7 (AF7 = USART3)
    LL_GPIO_SetPinMode(GPIOD, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(GPIOD, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(GPIOD, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(GPIOD, LL_GPIO_PIN_8, LL_GPIO_PULL_UP);
    LL_GPIO_SetAFPin_8_15(GPIOD, LL_GPIO_PIN_8, LL_GPIO_AF_7); // TX

    LL_GPIO_SetPinMode(GPIOD, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(GPIOD, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(GPIOD, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(GPIOD, LL_GPIO_PIN_9, LL_GPIO_PULL_UP);
    LL_GPIO_SetAFPin_8_15(GPIOD, LL_GPIO_PIN_9, LL_GPIO_AF_7); // RX

    // 4. Configure USART3: 115200 baud, 8N1
    //LL_USART_Disable(USART3);

    LL_USART_SetTransferDirection(USART3, LL_USART_DIRECTION_TX_RX);
    LL_USART_SetParity(USART3, LL_USART_PARITY_NONE);
    LL_USART_SetDataWidth(USART3, LL_USART_DATAWIDTH_8B);
    LL_USART_SetStopBitsLength(USART3, LL_USART_STOPBITS_1);
    LL_USART_SetOverSampling(USART3, LL_USART_OVERSAMPLING_16);
    LL_USART_SetBaudRate(USART3, SystemCoreClock/2, LL_USART_OVERSAMPLING_16, 115200); 
    // Note: APB1 clock is typically SystemCoreClock / 2, verify in your RCC config

    LL_USART_Enable(USART3);

    // 5. Wait until USART is ready
    while (!LL_USART_IsActiveFlag_TEACK(USART3))

    {
        __asm("nop");
    }
}

    
void uart_putc(char c)
{
    while (!LL_USART_IsActiveFlag_TXE(USART3))
    {
        __asm("nop");
    }

    LL_USART_TransmitData8(USART3, c);
}
*/




void uart_init()
{
    // 1. Enable GPIOA and USART1 clocks
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

    // 2. Set USART1 clock source (if required; STM32F7 usually defaults to PCLK1)
    // No need to call LL_RCC_SetUSARTClockSource for F7 unless you're changing the source

    // 3. Configure PA9 and PA10 as Alternate Function 7 (AF7 = USART1)
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_9, LL_GPIO_PULL_UP);
    LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_7); // TX

    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_10, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_10, LL_GPIO_PULL_UP);
    LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_7); // RX

    // 4. Configure USART1: 115200 baud, 8N1
    //LL_USART_Disable(USART1);

    LL_USART_SetTransferDirection(USART1, LL_USART_DIRECTION_TX_RX);
    LL_USART_SetParity(USART1, LL_USART_PARITY_NONE);
    LL_USART_SetDataWidth(USART1, LL_USART_DATAWIDTH_8B);
    LL_USART_SetStopBitsLength(USART1, LL_USART_STOPBITS_1);
    LL_USART_SetOverSampling(USART1, LL_USART_OVERSAMPLING_16);
    LL_USART_SetBaudRate(USART1, SystemCoreClock/2, LL_USART_OVERSAMPLING_16, 115200); 
    // Note: APB1 clock is typically SystemCoreClock / 2, verify in your RCC config

    LL_USART_Enable(USART1);

    // 5. Wait until USART is ready
    while (!LL_USART_IsActiveFlag_TEACK(USART1))

    {
        __asm("nop");
    }
}


void uart_putc(char c)
{
    while (!LL_USART_IsActiveFlag_TXE(USART1))
    {
        __asm("nop");
    }

    LL_USART_TransmitData8(USART1, c);
}