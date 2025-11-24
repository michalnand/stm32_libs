#include "tft_display_ll.h"


void TFTDisplayLL::ll_init()
{
    spi_init();
}

/*
uint8_t TFTDisplayLL::spib(uint8_t b)
{
    uint8_t result = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        // send bit, MSB first
        if (b&(1<<7))
        {
            mosi = 1;
        }
        else
        {
            mosi = 0;
        }

        b<<=1;
        
        // clck up
        sck = 1;   
        
        // read input
        result<<= 1;

        if (miso)
        {
            result|= 1;
        }
        
        sck = 0;    
    }

    return result;
}
*/

uint8_t TFTDisplayLL::spib(uint8_t b) 
{   
    // Wait until TX buffer is empty
    while (!LL_SPI_IsActiveFlag_TXE(SPI1));
    LL_SPI_TransmitData8(SPI1, b);  

    // Wait until data is received
    while (!LL_SPI_IsActiveFlag_RXNE(SPI1));
    return LL_SPI_ReceiveData8(SPI1);
}


void TFTDisplayLL::spi_init()
{
    // Enable clocks
    // For SPI1 on PA5 (SCK), PA6 (MISO), PA7 (MOSI)
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); 

    // Configure GPIOs for SPI1: PA5 = SCK, PA6 = MISO, PA7 = MOSI
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LL_GPIO_PIN_5 | LL_GPIO_PIN_6 | LL_GPIO_PIN_7;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);


    // Configure SPI1
    LL_SPI_Disable(SPI1);
    LL_SPI_SetTransferDirection(SPI1, LL_SPI_FULL_DUPLEX);

    LL_SPI_SetMode(SPI1, LL_SPI_MODE_MASTER);
    LL_SPI_SetDataWidth(SPI1, LL_SPI_DATAWIDTH_8BIT);
    LL_SPI_SetClockPolarity(SPI1, LL_SPI_POLARITY_LOW);
    LL_SPI_SetClockPhase(SPI1, LL_SPI_PHASE_1EDGE);
    LL_SPI_SetNSSMode(SPI1, LL_SPI_NSS_SOFT); // Software NSS
    LL_SPI_SetBaudRatePrescaler(SPI1, LL_SPI_BAUDRATEPRESCALER_DIV4);
    //LL_SPI_SetBitOrder(SPI1, LL_SPI_MSB_FIRST);
    LL_SPI_SetRxFIFOThreshold(SPI1, LL_SPI_RX_FIFO_TH_QUARTER);

    LL_SPI_Enable(SPI1);
}

