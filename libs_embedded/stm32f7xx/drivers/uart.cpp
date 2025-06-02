#include "uart.h"

#include "drivers.h"



void uart_init()
{
    // 1. Enable GPIOA and USART2 clocks
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

    //LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);


    // 2. Configure PA2 and PA3 to Alternate Function (AF1), High Speed, Push-Pull
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_2, 1); // AF1 for USART2_TX

    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_2, LL_GPIO_PULL_UP);
    
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_3, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_3, 1); // AF1 for USART2_RX
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_3, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_3, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_3, LL_GPIO_PULL_UP);
    
    // 3. Configure USART2: 115200 baud, 8N1
    LL_USART_SetTransferDirection(USART2, LL_USART_DIRECTION_TX_RX);
    LL_USART_SetParity(USART2, LL_USART_PARITY_NONE);
    LL_USART_SetDataWidth(USART2, LL_USART_DATAWIDTH_8B);
    LL_USART_SetStopBitsLength(USART2, LL_USART_STOPBITS_1);


    LL_USART_SetBaudRate(USART2,
        SystemCoreClock,
        LL_USART_PRESCALER_DIV1,
        LL_USART_OVERSAMPLING_16,
        115200);
      
    
    // 4. Enable USART
    LL_USART_Enable(USART2);
    
    // 5. Wait until USART is ready
    while (!(LL_USART_IsActiveFlag_TEACK(USART2)) || !(LL_USART_IsActiveFlag_REACK(USART2)))
    {
        __asm("nop");
    }
}

    
void uart_putc(char c)
{
    // Wait until TXE (transmit buffer empty)
    while (!LL_USART_IsActiveFlag_TXE(USART2))
    {
        __asm("nop");
    }
    
    LL_USART_TransmitData8(USART2, c);
}
