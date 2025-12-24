#ifndef _TFT_DISPLAY_H_
#define _TFT_DISPLAY_H_

#include "drivers.h"
#include "tft_display_ll.h"


#define DISPLAY_HEIGHT ((uint32_t)320)
#define DISPLAY_WIDTH  ((uint32_t)240)
    

class TFTDisplay: public TFTDisplayLL
{
    public:
        void init();

        void set_addr_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        void draw_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
        void fill_screen(uint8_t r, uint8_t g, uint8_t b);

        void set_full_screen();
        void set_pixel(uint8_t r, uint8_t g, uint8_t b);
        void set_pixel_rgb565(uint16_t value);
        void end_full_screen();


        uint32_t height()
        {
            return DISPLAY_HEIGHT;
        }

        uint32_t width()
        {
            return DISPLAY_WIDTH;
        }

    private:
        uint16_t rgb888_to_rgb565(uint8_t r, uint8_t g, uint8_t b);

        void delay_ms(uint32_t loops);


    private:

        void write_command(uint8_t cmd);
        void write_data(uint8_t data);
        void write_data16(uint16_t data);
        
};

#endif