#ifndef SSD1315_H_
#define SSD1315_H_

#include "i2c_interface.h"


#define OLED_N_ROWS     ((unsigned char)8)
#define OLED_N_COLS     ((unsigned char)16)


class SSD1315
{
    public:
        SSD1315();
        void init(I2C_Interface &i2c);

    public:
        void clear();
        void set_brightness(unsigned char brightness);
        
        void set_text_xy(unsigned char row, unsigned char column);
        void put_char(unsigned char chr);
        void put_string(char *s, unsigned char row = 0);

        void put_info(char *text, int value, unsigned char row);



    private:
        void send_command(unsigned char command);
        void send_data(unsigned char data);
        void send_data_batch(unsigned char *data, unsigned char count);


    private:
        I2C_Interface *i2c; 
};




#endif