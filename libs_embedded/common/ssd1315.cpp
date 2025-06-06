#include "ssd1315.h"




#define SeeedOLED_Max_X                 127 //128 Pixels
#define SeeedOLED_Max_Y                 63  //64  Pixels

#define PAGE_MODE                       01
#define HORIZONTAL_MODE                 02


#define SeeedOLED_Address               (0x3c << 1)
#define SeeedOLED_Command_Mode          0x80
#define SeeedOLED_Data_Mode             0x40
#define SeeedOLED_Display_Off_Cmd       0xAE
#define SeeedOLED_Display_On_Cmd        0xAF
#define SeeedOLED_Normal_Display_Cmd    0xA6
#define SeeedOLED_Inverse_Display_Cmd   0xA7
#define SSD1315_SET_MULTI_PLEX          0xA8
#define SeeedOLED_Activate_Scroll_Cmd   0x2F
#define SeeedOLED_Dectivate_Scroll_Cmd  0x2E
#define SSD1315_SET_DISPLAY_CLK_DIV     0xD5
#define SeeedOLED_Set_Brightness_Cmd    0x81
#define SSD1315_CHARGE_PUMP             0x8D

#define Scroll_Left             0x00
#define Scroll_Right            0x01

#define Scroll_2Frames          0x7
#define Scroll_3Frames          0x4
#define Scroll_4Frames          0x5
#define Scroll_5Frames          0x0
#define Scroll_25Frames         0x6
#define Scroll_64Frames         0x1
#define Scroll_128Frames        0x2
#define Scroll_256Frames        0x3

    
    
const unsigned char font_table[][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00},
    {0x00, 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00, 0x00},
    {0x00, 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00, 0x00},
    {0x00, 0x23, 0x13, 0x08, 0x64, 0x62, 0x00, 0x00},
    {0x00, 0x36, 0x49, 0x55, 0x22, 0x50, 0x00, 0x00},
    {0x00, 0x00, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x1C, 0x22, 0x41, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x41, 0x22, 0x1C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00, 0x00},
    {0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00},
    {0x00, 0xA0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00},
    {0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00},
    {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x00},
    {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, 0x00},
    {0x00, 0x62, 0x51, 0x49, 0x49, 0x46, 0x00, 0x00},
    {0x00, 0x22, 0x41, 0x49, 0x49, 0x36, 0x00, 0x00},
    {0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00, 0x00},
    {0x00, 0x27, 0x45, 0x45, 0x45, 0x39, 0x00, 0x00},
    {0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00, 0x00},
    {0x00, 0x01, 0x71, 0x09, 0x05, 0x03, 0x00, 0x00},
    {0x00, 0x36, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00},
    {0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, 0x00, 0x00},
    {0x00, 0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xAC, 0x6C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00, 0x00},
    {0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00, 0x00},
    {0x00, 0x41, 0x22, 0x14, 0x08, 0x00, 0x00, 0x00},
    {0x00, 0x02, 0x01, 0x51, 0x09, 0x06, 0x00, 0x00},
    {0x00, 0x32, 0x49, 0x79, 0x41, 0x3E, 0x00, 0x00},
    {0x00, 0x7E, 0x09, 0x09, 0x09, 0x7E, 0x00, 0x00},
    {0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00},
    {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00, 0x00},
    {0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, 0x00, 0x00},
    {0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00, 0x00},
    {0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00, 0x00},
    {0x00, 0x3E, 0x41, 0x41, 0x51, 0x72, 0x00, 0x00},
    {0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, 0x00},
    {0x00, 0x41, 0x7F, 0x41, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, 0x00, 0x00},
    {0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00},
    {0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00},
    {0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00, 0x00},
    {0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00, 0x00},
    {0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00, 0x00},
    {0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00, 0x00},
    {0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00, 0x00},
    {0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00, 0x00},
    {0x00, 0x26, 0x49, 0x49, 0x49, 0x32, 0x00, 0x00},
    {0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, 0x00, 0x00},
    {0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00, 0x00},
    {0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00, 0x00},
    {0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00, 0x00},
    {0x00, 0x63, 0x14, 0x08, 0x14, 0x63, 0x00, 0x00},
    {0x00, 0x03, 0x04, 0x78, 0x04, 0x03, 0x00, 0x00},
    {0x00, 0x61, 0x51, 0x49, 0x45, 0x43, 0x00, 0x00},
    {0x00, 0x7F, 0x41, 0x41, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00},
    {0x00, 0x41, 0x41, 0x7F, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x04, 0x02, 0x01, 0x02, 0x04, 0x00, 0x00},
    {0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00},
    {0x00, 0x01, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x20, 0x54, 0x54, 0x54, 0x78, 0x00, 0x00},
    {0x00, 0x7F, 0x48, 0x44, 0x44, 0x38, 0x00, 0x00},
    {0x00, 0x38, 0x44, 0x44, 0x28, 0x00, 0x00, 0x00},
    {0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, 0x00, 0x00},
    {0x00, 0x38, 0x54, 0x54, 0x54, 0x18, 0x00, 0x00},
    {0x00, 0x08, 0x7E, 0x09, 0x02, 0x00, 0x00, 0x00},
    {0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, 0x00, 0x00},
    {0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00, 0x00},
    {0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x80, 0x84, 0x7D, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00},
    {0x00, 0x41, 0x7F, 0x40, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, 0x00, 0x00},
    {0x00, 0x7C, 0x08, 0x04, 0x7C, 0x00, 0x00, 0x00},
    {0x00, 0x38, 0x44, 0x44, 0x38, 0x00, 0x00, 0x00},
    {0x00, 0xFC, 0x24, 0x24, 0x18, 0x00, 0x00, 0x00},
    {0x00, 0x18, 0x24, 0x24, 0xFC, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7C, 0x08, 0x04, 0x00, 0x00, 0x00},
    {0x00, 0x48, 0x54, 0x54, 0x24, 0x00, 0x00, 0x00},
    {0x00, 0x04, 0x7F, 0x44, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x3C, 0x40, 0x40, 0x7C, 0x00, 0x00, 0x00},
    {0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00, 0x00},
    {0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00, 0x00},
    {0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 0x00},
    {0x00, 0x1C, 0xA0, 0xA0, 0x7C, 0x00, 0x00, 0x00},
    {0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00, 0x00},
    {0x00, 0x08, 0x36, 0x41, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x41, 0x36, 0x08, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x02, 0x01, 0x01, 0x02, 0x01, 0x00, 0x00},
    {0x00, 0x02, 0x05, 0x05, 0x02, 0x00, 0x00, 0x00}
};


SSD1315::SSD1315()
{

}

void SSD1315::init(I2C_Interface &i2c)
{
    this->i2c = &i2c;


    send_command(0xAE);//--display off
  
    send_command(0x00);//--set low column address
    send_command(0x10);//--set high column address
    send_command(0x40);//--set start line address  
    
    send_command(0xB0);//--set page address
    
    send_command(0x81);// contract control
    send_command(0xFF);//--128   
    send_command(0xA1);//set segment re-map  0 to 127 
    send_command(0xA6);//set normal  display  
    send_command(0xA8);//set multiplex ratio(1 to 64)
    send_command(0x3F);//--1/32 duty
    
    send_command(0xC8);//Com scan direction
    send_command(0xD3);//set display offset
    send_command(0x00);//no offset
        
    send_command(0xD5);//set display clock divide ratio/oscillator frequency  
    send_command(0x80);//
        
    send_command(0xD8);//set area color mode off
    send_command(0x05);//
        
    send_command(0xD9);//Set Pre-Charge Period
    send_command(0xF1);//
        
    send_command(0xDA);//set com pin  hardware configuartion
    send_command(0x12);//
        
    send_command(0xDB);//set Vcomh
    send_command(0x30);//0x20,0.77xVcc
        
    send_command(0x8D);//set charge pump enable
    send_command(0x14);//
        
    send_command(0xAF);//--turn on oled panel


    clear();
}   

    
void SSD1315::send_command(unsigned char command)
{
    i2c->start();

    i2c->write(SeeedOLED_Address);
    i2c->write(SeeedOLED_Command_Mode);
    i2c->write(command);

    i2c->stop();
}

void SSD1315::send_data(unsigned char data)
{
    i2c->start();

    i2c->write(SeeedOLED_Address);
    i2c->write(SeeedOLED_Data_Mode);
    i2c->write(data);

    i2c->stop();
}


void SSD1315::clear()
{
    for (unsigned char j = 0; j < OLED_N_ROWS; j++)
    {
        set_text_xy(j, 0);
        for (unsigned char i = 0; i < OLED_N_COLS; i++)
        {
            for (unsigned char b = 0; b < 8; b++) 
            {
                send_data(0x00);
            }
        }   
    }
}



void SSD1315::set_brightness(unsigned char brightness) 
{
    send_command(SeeedOLED_Set_Brightness_Cmd);
    send_command(brightness);
}

void SSD1315::set_text_xy(unsigned char row, unsigned char column) 
{
    send_command(0xB0 + row);            
    send_command(0x00 + (8 * column & 0x0F));
    send_command(0x10 + ((8 * column >> 4) & 0x0F));
}


void SSD1315::put_char(unsigned char chr) 
{
    if (chr < 32 || chr > 127) 
    { 
        chr = ' '; 
    }

    for (unsigned char i = 0; i < 8; i++) 
    {
        unsigned char b =  font_table[chr - 32][i];
        send_data(b);
    }
}

void SSD1315::put_string(char *s, unsigned char row)
{
    set_text_xy(row, 0);

    i2c->start();

    i2c->write(SeeedOLED_Address);
    i2c->write(SeeedOLED_Data_Mode);


    unsigned char i = 0;
    while (i < OLED_N_COLS && s[i] != 0)
    {
        unsigned char chr = s[i];

        if (chr < 32 || chr > 127) 
        { 
            chr = ' '; 
        }

        for (unsigned char j = 0; j < 8; j++) 
        {
            unsigned char b = font_table[chr - 32][j];
            i2c->write(b);
        }

        i++;
    }   

    i2c->stop();
}


void SSD1315::put_info(char *text, int value, unsigned char row)
{
    char buffer[OLED_N_COLS+1];

    for (unsigned char i = 0; i < OLED_N_COLS; i++)
    {
        buffer[i] = ' ';
    }

    buffer[OLED_N_COLS] = 0;

    unsigned char i = 0;
    while (i < OLED_N_COLS && text[i] != 0)
    {
        buffer[i] = text[i];
        i++;
    }

    char sgn = 0;
    if (value < 0)
    {
        sgn = 1;
        value = -value;
    }

    i = OLED_N_COLS-1;
    do
    {
        buffer[i] = '0' + (value%10);
        value/=10;
        i--;
    }
    while (value != 0 && i > 0);

    if (sgn)
    {
        buffer[i] = '-';
    }


    put_string(buffer, row);
}
