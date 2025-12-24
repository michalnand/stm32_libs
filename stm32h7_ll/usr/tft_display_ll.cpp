#include "tft_display_ll.h"

#include "stm32h7xx.h"
#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_gpio.h"
#include "stm32h7xx_ll_spi.h"


#define spi_delay() {__asm("nop");}

void TFTDisplayLL::ll_init()
{
    // spi_init();
}



uint8_t TFTDisplayLL::spib(uint8_t b) 
{     
    /*
    //LL_SPI_StartMasterTransfer(SPI2);
    while (LL_SPI_IsActiveFlag_TXP(SPI2) == 0)
    {
        __asm("nop");
    }

    LL_SPI_TransmitData8(SPI2, b);

    return 0;
    */
    /*
    while (!LL_SPI_IsActiveFlag_RXWNE(SPI2));
    return LL_SPI_ReceiveData8(SPI2);
    */

    uint8_t result = 0;
    for (unsigned int i = 0; i < 8; i++)
    {
        result<<= 1;

        if (b&(1<<7))
            mosi = 1;
        else
            mosi = 0;

        spi_delay();
        
        sck = 1;
        spi_delay();

        if (miso)
        {
            result|= (1<<0);
        }

        sck = 0;
        spi_delay();

        b<<= 1;
    }


    return result;
}


void TFTDisplayLL::spi_init()
{
    // Enable clocks 
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);

    // GPIO PB13(SCK), PB14(MISO), PB15(MOSI) -> AF5
    LL_GPIO_InitTypeDef gpio = {0};

    gpio.Pin        = LL_GPIO_PIN_13 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15;
    gpio.Mode       = LL_GPIO_MODE_ALTERNATE;
    gpio.Speed      = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio.Pull       = LL_GPIO_PULL_NO;
    gpio.Alternate  = LL_GPIO_AF_5;
    LL_GPIO_Init(GPIOB, &gpio);

    
    LL_SPI_InitTypeDef SPI_InitStruct = {};
    SPI_InitStruct.Mode              = LL_SPI_MODE_MASTER;
    SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
    SPI_InitStruct.ClockPhase        = LL_SPI_PHASE_1EDGE;
    SPI_InitStruct.ClockPolarity     = LL_SPI_POLARITY_LOW;
    SPI_InitStruct.BitOrder          = LL_SPI_MSB_FIRST;
    SPI_InitStruct.DataWidth         = LL_SPI_DATAWIDTH_8BIT;
    SPI_InitStruct.NSS               = LL_SPI_NSS_SOFT; // no NSS, using a GPIO as SS!
    SPI_InitStruct.CRCCalculation    = LL_SPI_CRCCALCULATION_DISABLE;
    SPI_InitStruct.BaudRate          = 32;
    LL_SPI_Init(SPI2, &SPI_InitStruct);
    
    // This locks SPI pins in AF mode when the SPI is disabled, to avoid glitches on CLK
    // Temporary disable may be required to recover from weird states; see errata - pa01
    //LL_SPI_EnableGPIOControl(SPI2);
    //LL_SPI_DisableMasterRxAutoSuspend(SPI2);

    // Set transfer size = 0 (not using 'transfers')
    LL_SPI_SetTransferSize(SPI2, 1);
    LL_SPI_SetFIFOThreshold(SPI2, LL_SPI_FIFO_TH_01DATA);

    // Enable the SPI
    LL_SPI_Enable(SPI2);
    

    // Start master in automatic (no-transaction) mode
    LL_SPI_StartMasterTransfer(SPI2);
}

