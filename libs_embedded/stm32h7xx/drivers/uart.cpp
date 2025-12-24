#include "uart.h"

#include "drivers.h"



void uart_init(void)
{
    /*----------------------------------------------------------*/
    /* Enable clocks                                             */
    /*----------------------------------------------------------*/

    /* GPIOA clock (AHB4 on H7) */
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);

    /* USART1 clock (APB2) */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

    /*----------------------------------------------------------*/
    /* Select USART1 clock source                                */
    /*----------------------------------------------------------*/
    /*
     * On STM32H7 this MUST be set explicitly.
     * Use PCLK2 = 100 MHz
     */
    LL_RCC_SetUSARTClockSource(LL_RCC_USART16_CLKSOURCE_PCLK2);

    /*----------------------------------------------------------*/
    /* GPIO configuration: PA9 (TX), PA10 (RX)                   */
    /*----------------------------------------------------------*/

    /* PA9 - TX */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_9, LL_GPIO_PULL_UP);
    LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_7);

    /* PA10 - RX */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_10, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_10, LL_GPIO_PULL_UP);
    LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_7);

    /*----------------------------------------------------------*/
    /* USART configuration                                       */
    /*----------------------------------------------------------*/

    LL_USART_Disable(USART1);

    LL_USART_SetTransferDirection(USART1, LL_USART_DIRECTION_TX_RX);
    LL_USART_SetParity(USART1, LL_USART_PARITY_NONE);
    LL_USART_SetDataWidth(USART1, LL_USART_DATAWIDTH_8B);
    LL_USART_SetStopBitsLength(USART1, LL_USART_STOPBITS_1);
    LL_USART_SetOverSampling(USART1, LL_USART_OVERSAMPLING_16);

    /*
     * IMPORTANT (H7):
     * Baud rate must use the ACTUAL USART kernel clock,
     * here PCLK2 = 100 MHz
     */
   

    LL_USART_SetBaudRate(
        USART1,
        100000000U,                  /* USART kernel clock (PCLK2) */
        LL_USART_PRESCALER_DIV1,     /* Prescaler */
        LL_USART_OVERSAMPLING_16,
        115200U
    );

    LL_USART_Enable(USART1);

    /*----------------------------------------------------------*/
    /* Wait until USART is ready                                 */
    /*----------------------------------------------------------*/

    while (!LL_USART_IsActiveFlag_TEACK(USART1));
    while (!LL_USART_IsActiveFlag_REACK(USART1));
}


void uart_putc(char c)
{
    while (!LL_USART_IsActiveFlag_TXE_TXFNF(USART1))
    {
        __asm("nop");
    }

    LL_USART_TransmitData8(USART1, (uint8_t)c);
}