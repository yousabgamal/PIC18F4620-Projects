/* 
 * File:   ecu_led.c
 * Author: Ibrahim Shenouda
 *
 * Created on 22 Nov, 2024, 03:13 ?
 */

/******************Section: Includes**********************/
#include "ecu_led.h"
/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_initialize(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = 
        {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_DIRECTION_OUTPUT,
        .logic = led->led_status      
        };
        
        gpio_pin_intialize(&pin_obj);
    } 
    return ret;
}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_on(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = 
        {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_DIRECTION_OUTPUT,
        .logic = led->led_status      
        };
        
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    } 
    return ret;
}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_off(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = 
        {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_DIRECTION_OUTPUT,
        .logic = led->led_status      
        };
        
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    } 
    return ret;    
}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_toggle(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = 
        {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_DIRECTION_OUTPUT,
        .logic = led->led_status      
        };
        
        gpio_pin_toggle_logic(&pin_obj);
    } 
    return ret;    
}
