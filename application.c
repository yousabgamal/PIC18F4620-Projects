/* 
 * File:   application.c
 * Author: Yousab Gamal
 * Created on 22 Nov, 2024, 03:13 ?
 */

#include "application.h"
#include "ECU_Layer/Chr_LCD/ecu_chr_LCD.h"
#include "MCAL_Layer/ADC/hal_adc.h"

dc_motor_t motor_1 = {
    .dc_motor_pin[0].port      = PORTD_INDEX,
    .dc_motor_pin[0].pin       = GPIO_PIN2,
    .dc_motor_pin[0].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    
    .dc_motor_pin[1].port      = PORTD_INDEX,
    .dc_motor_pin[1].pin       = GPIO_PIN3,
    .dc_motor_pin[1].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT
};

dc_motor_t motor_2 = {
    .dc_motor_pin[0].port      = PORTD_INDEX,
    .dc_motor_pin[0].pin       = GPIO_PIN4,
    .dc_motor_pin[0].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    
    .dc_motor_pin[1].port      = PORTD_INDEX,
    .dc_motor_pin[1].pin       = GPIO_PIN5,
    .dc_motor_pin[1].logic     = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT
};

adc_conf_t adc = {
    .ADC_InterruptHandler = NULL,
    .adc_channel          = ADC_CHANNEL_AN0,
    .aquizition_time      = ADC_12_TAD,
    .conversion_clock     = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format        = ADC_RESULT_RIGHT,
    .voltage_ref          = ADC_VOLTAGE_REFERENCE_DISABLE
};

uint16 lm35_res_1, lm35_res_2;
uint16 lm35_res_1_Celsius = 0, lm35_res_2_Celsius = 0;
uint8 lm35_res_1_txt[6], lm35_res_2_txt[6];

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initializetion();
    
    ret = lcd_8bit_send_string_pos(&lcd_2 , 1 , 5 , "Temp test...");
    __delay_ms(2000);
    ret = lcd_8bit_send_command(&lcd_2 , _LCD_CLEAR);
    
    ret = lcd_8bit_send_string_pos(&lcd_2 , 1 , 1 , "Sensor 1: ");
    ret = lcd_8bit_send_string_pos(&lcd_2 , 2 , 1 , "Sensor 2: ");
    
    while(1)
    {
        ret = ADC_GetConversion_Blocking(&adc , ADC_CHANNEL_AN0 , &lm35_res_1);
        ret = ADC_GetConversion_Blocking(&adc , ADC_CHANNEL_AN1 , &lm35_res_2);
        
        lm35_res_1_Celsius = lm35_res_1 * 4.88f;
        lm35_res_2_Celsius = lm35_res_2 * 4.88f;
        lm35_res_1_Celsius /= 10;
        lm35_res_2_Celsius /= 10;
        
        ret = convert_short_to_string(lm35_res_1_Celsius , lm35_res_1_txt);
        ret = convert_short_to_string(lm35_res_2_Celsius , lm35_res_2_txt);
        
        ret = lcd_8bit_send_string_pos(&lcd_2 , 1 , 11 , lm35_res_1_txt);
        ret = lcd_8bit_send_string_pos(&lcd_2 , 2 , 11 , lm35_res_2_txt);
        
        if(lm35_res_1_Celsius >= 20)
        {
            ret = dc_motor_move_right(&motor_1);
        }
        else
        {
            ret = dc_motor_stop(&motor_1);
        }
        if(lm35_res_2_Celsius < 20)
        {
            ret = dc_motor_move_left(&motor_2);
        }
        else
        {
            ret = dc_motor_stop(&motor_2);
        }
    }
    return (EXIT_SUCCESS);
}
void application_initializetion()
{
    Std_ReturnType ret = E_NOT_OK; 
    ret = ADC_Init(&adc);
    ecu_layer_initialize();
    ret = dc_motor_initialize(&motor_1);
    ret = dc_motor_initialize(&motor_2);
}
