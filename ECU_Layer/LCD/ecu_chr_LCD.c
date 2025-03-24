/* 
 * File:   ecu_chr_LCD.c
 * Author: yousg
 *
 * Created on March 4, 2025, 2:37 PM
 */

#include "ecu_chr_LCD.h"

static Std_ReturnType lcd_send_4bits(const chr_lcd_8bit_t * lcd , uint8 _data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_8bit_t * lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t * lcd);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t * lcd , uint8 row , uint8 column);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t * lcd , uint8 row , uint8 column);


Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t * lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 data_pins_counter = 0 ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(data_pins_counter = 0 ; data_pins_counter < 4 ; data_pins_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd , _LCD_4BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd , _LCD_4BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd , _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd , _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd , _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd , _LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd , _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd , _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd , 0x80);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t * lcd , uint8 command)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW);
        ret = lcd_send_4bits(lcd , command >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd , command);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_data(const chr_lcd_4bit_t * lcd , uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH);
        ret = lcd_send_4bits(lcd , data >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd , data);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_data_pos(const chr_lcd_4bit_t * lcd , uint8 row , uint8 column , uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd , row , column);
        ret = lcd_4bit_send_data(lcd , data);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t * lcd , uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) || (NULL == str))
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_4bit_send_data(lcd , *str++);
        }
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t * lcd , uint8 row , uint8 column ,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) || (NULL == str))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd , row , column);
        while(*str)
        {
            ret = lcd_4bit_send_data(lcd , *str++);
        }
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_custome_char(const chr_lcd_4bit_t * lcd , uint8 row , uint8 column , 
                                          const uint8 chr[] , uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter = 0 ; lcd_counter <= 7 ; lcd_counter++)
        {
            ret = lcd_4bit_send_data(lcd , chr[lcd_counter]);
        }
        ret = lcd_4bit_send_data_pos(lcd , row , column , mem_pos);
    }
    return ret;
}


Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t * lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 data_pins_counter = 0 ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(data_pins_counter = 0 ; data_pins_counter < 8 ; data_pins_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd , _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd , _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd , _LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd , _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd , 0x80);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t * lcd , uint8 command)
{
    Std_ReturnType ret = E_OK;
    uint8 pin_counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW);
        for(pin_counter = 0; pin_counter < 8 ;pin_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[pin_counter]), command >>pin_counter & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_data(const chr_lcd_8bit_t * lcd , uint8 data)
{
    Std_ReturnType ret = E_OK;
    uint8 pin_counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH);
        for(pin_counter = 0; pin_counter < 8 ;pin_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[pin_counter]), data >>pin_counter & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_data_pos(const chr_lcd_8bit_t * lcd , uint8 row , uint8 column , uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor(lcd , row , column);
        ret = lcd_8bit_send_data(lcd , data);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t * lcd , uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) || (NULL == str))
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_8bit_send_data(lcd , *str);
            str++;
        }
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t * lcd , uint8 row , uint8 column ,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) || (NULL == str))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor(lcd , row , column);
        while(*str)
        {
            ret = lcd_8bit_send_data(lcd , *str);
            str++;
        }
        
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_custome_char(const chr_lcd_8bit_t * lcd , uint8 row , uint8 column , 
                                          const uint8 chr[] , uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter = 0 ; lcd_counter <= 7 ; lcd_counter++)
        {
            ret = lcd_8bit_send_data(lcd , chr[lcd_counter]);
        }
        ret = lcd_8bit_send_data_pos(lcd , row , column , mem_pos);
    }
    return ret;
}


Std_ReturnType convert_byte_to_string(uint8 value , uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str , '\0' , 4);
        sprintf(str , "%i" , value);
    }
    return ret;
}

Std_ReturnType convert_short_to_string(uint16 value , uint8 *str)
{
    Std_ReturnType ret = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str , ' ' , 5);
        str[5] = '\0';
        sprintf((char*)Temp_String , "%i" , value);
        while(Temp_String[DataCounter] != '\0')
        {
            str[DataCounter] = Temp_String[DataCounter];
            DataCounter++;
        }
    }
    return ret;
}

Std_ReturnType convert_int_to_string(uint32 value , uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str , '\0' , 11);
        sprintf(str , "%i" , value);
    }
    return ret;
}

static Std_ReturnType lcd_send_4bits(const chr_lcd_8bit_t * lcd , uint8 _data_command)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        //low nipple
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), _data_command >>0 & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), _data_command >>1 & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), _data_command >>2 & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), _data_command >>3 & (uint8)0x01);
    }
    return ret;
}

static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_8bit_t * lcd)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        //low nipple
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t * lcd)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t * lcd , uint8 row , uint8 column)
{
    Std_ReturnType ret = E_OK;
    column--;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(row)
        {
            case ROW1:
                ret = lcd_8bit_send_command(lcd , (0x80 + column));
                break;
            case ROW2:
                ret = lcd_8bit_send_command(lcd , (0xC0 + column));
                break;
            case ROW3:
                ret = lcd_8bit_send_command(lcd , (0x94 + column));
                break;
            case ROW4:
                ret = lcd_8bit_send_command(lcd , (0xD4 + column));
                break;
            default:/*NOTHING*/;
        }
    }
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t * lcd , uint8 row , uint8 column)
{
    Std_ReturnType ret = E_OK;
    column--;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(row)
        {
            case ROW1:
                ret = lcd_4bit_send_command(lcd , (0x80 + column));
                break;
            case ROW2:
                ret = lcd_4bit_send_command(lcd , (0xC0 + column));
                break;
            case ROW3:
                ret = lcd_4bit_send_command(lcd , (0x94 + column));
                break;
            case ROW4:
                ret = lcd_4bit_send_command(lcd , (0xD4 + column));
                break;
            default:/*NOTHING*/;
        }
    }
    return ret;
}
