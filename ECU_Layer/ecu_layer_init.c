/* 
 * File:   ecu_layer_init.c
 * Author: yousg
 *
 * Created on March 4, 2025, 2:40 PM
 */

#include "ecu_layer_init.h"

chr_lcd_4bit_t lcd_1= {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.logic = GPIO_LOW,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].logic = GPIO_LOW,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    
};

chr_lcd_8bit_t lcd_2= {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.logic = GPIO_LOW,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].logic = GPIO_LOW,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[4].port = PORTC_INDEX,
    .lcd_data[4].pin = GPIO_PIN6,
    .lcd_data[4].logic = GPIO_LOW,
    .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[5].port = PORTC_INDEX,
    .lcd_data[5].pin = GPIO_PIN7,
    .lcd_data[5].logic = GPIO_LOW,
    .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[6].port = PORTD_INDEX,
    .lcd_data[6].pin = GPIO_PIN0,
    .lcd_data[6].logic = GPIO_LOW,
    .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
    
    .lcd_data[7].port = PORTD_INDEX,
    .lcd_data[7].pin = GPIO_PIN1,
    .lcd_data[7].logic = GPIO_LOW,
    .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
    
};

void ecu_layer_initialize()
{
    Std_ReturnType ret = E_OK;
    //ret = lcd_4bit_initialize(&lcd_1);//error in this fun
    ret = lcd_8bit_initialize(&lcd_2);
};