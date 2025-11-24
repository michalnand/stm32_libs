#include "tft_display.h"


void TFTDisplay::init()
{
    ll_init();

    reset = 0;
    delay_ms(50);
    reset = 1;
    delay_ms(50);

    bl = 1;

    // Software reset
    write_command(0x01); // SWRESET
    delay_ms(50);

    write_command(0x11); // SLPOUT
    delay_ms(50);

    write_command(0x3A); // COLMOD: Pixel Format Set
    write_data(0x55);    // 16-bit color (RGB565)

    write_command(0x36); // MADCTL: Memory Access Control
    write_data(0x00);    // Depending on rotation (0x00 = default portrait)

    write_command(0x21); // INVON: Display Inversion ON

    write_command(0x13); // NORON
    delay_ms(10);

    write_command(0x29); // DISPON
    delay_ms(50);

    fill_screen(100, 100, 100);
}

void TFTDisplay::set_addr_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) 
{
    write_command(0x2A); // CASET (Column Address Set)
    write_data16(x0);
    write_data16(x1);

    write_command(0x2B); // RASET (Row Address Set)
    write_data16(y0);
    write_data16(y1);

    write_command(0x2C); // RAMWR (Write to RAM)
}

void TFTDisplay::draw_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) 
{
    uint16_t color = rgb888_to_rgb565(r, g, b);
    set_addr_window(x, y, x, y);
    write_data16(color);
}


void TFTDisplay::set_full_screen()
{
    set_addr_window(0, 0, DISPLAY_WIDTH-1, DISPLAY_HEIGHT-1);  // Full screen
    //set_addr_window(0, 0, DISPLAY_HEIGHT-1, DISPLAY_WIDTH-1);  // Full screen

    dc = 1; //data mode
    cs = 0;
}

void TFTDisplay::set_pixel(uint8_t r, uint8_t g, uint8_t b)
{
    uint16_t color = rgb888_to_rgb565(r, g, b);
    write_data16(color);
}

void TFTDisplay::set_pixel_rgb565(uint16_t value)
{
    write_data16(value);
}
    
void TFTDisplay::end_full_screen()
{
    cs = 1;
    dc = 0;
}

void TFTDisplay::fill_screen(uint8_t r, uint8_t g, uint8_t b) 
{
    uint16_t color = rgb888_to_rgb565(r, g, b);

    set_addr_window(0, 0, DISPLAY_WIDTH-1, DISPLAY_HEIGHT-1);  // Full screen

    dc = 1;
    cs = 0;
    for (uint32_t i = 0; i < (DISPLAY_WIDTH * DISPLAY_HEIGHT); i++) 
    {
        spib(color >> 8);
        spib(color & 0xFF);
    }

    cs = 1;
}

uint16_t TFTDisplay::rgb888_to_rgb565(uint8_t r, uint8_t g, uint8_t b) 
{
    return ((r & 0xF8) << 8) |  // RRRRR00000000000
           ((g & 0xFC) << 3) |  // 00000GGGGG000000
           (b >> 3);            // 00000000000BBBBB
}



void TFTDisplay::delay_ms(uint32_t loops)
{   
    loops = loops*216000;

    while (loops--)
    {
        __asm("nop");
    }
}



void TFTDisplay::write_command(uint8_t cmd) 
{
    dc = 0;       // Command mode
    cs = 0;
    spib(cmd);
    cs = 1;
}

void TFTDisplay::write_data(uint8_t data) 
{
    dc = 1;      // Data mode
    cs = 0;
    spib(data);
    cs = 1; 
}

void TFTDisplay::write_data16(uint16_t data) 
{
    write_data(data >> 8);     // High byte
    write_data(data & 0xFF);   // Low byte
}
