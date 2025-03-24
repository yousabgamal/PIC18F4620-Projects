/* 
 * File:   hal_gpio.c
 * Author: Ibrahim Shenouda
 *
 * Created on 22 Nov, 2024, 03:37 PM
 */

#include "hal_gpio.h"

volatile uint8 *tris_registers[5] = {&TRISA_REG , &TRISB_REG , &TRISC_REG , &TRISD_REG , &TRISE_REG };
volatile uint8 *lat_registers[]  = {&LATA_REG , &LATB_REG , &LATC_REG , &LATD_REG, &LATE_REG };
volatile uint8 *port_registers[] = {&PORTA_REG , &PORTB_REG , &PORTC_REG , &PORTD_REG , &PORTE_REG };

/**********************pin functions*********************************/
/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGRATIONS==CONfIG_ENABLE
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        switch(_pin_config->direction)
        {
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
                break;
        
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
                break;
        
            default: ret = E_NOT_OK ;
        }
    }
    return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGRATIONS==CONfIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == direction_status || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = READ_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */

#if GPIO_PORT_PIN_CONFIGRATIONS==CONfIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(logic)
        {
            case GPIO_LOW:
                CLEAR_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
                break;
        
            case GPIO_HIGH:
                SET_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
                break;
        
            default: ret = E_NOT_OK ;
        }
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGRATIONS==CONfIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == logic || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*port_registers[_pin_config->port],_pin_config->pin);
    }
    return ret;    
}
#endif

/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGRATIONS==CONfIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
    }
    return ret;    
}
#endif

#if GPIO_PORT_PIN_CONFIGRATIONS==CONfIG_ENABLE
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_intialize(_pin_config);
        ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    return ret;    
}
#endif

/**********************port functions*********************************/

/**
 * 
 * @param port
 * @param direction
 * @return 
 */
#if GPIO_PORT_CONFIGRATIONS==CONfIG_ENABLE
Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction)
{
    Std_ReturnType ret = E_OK;
    
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *tris_registers[port] = direction;
    }
    return ret;   
}
#endif

/**
 * 
 * @param port
 * @param direction_status
 * @return 
 */
#if GPIO_PORT_CONFIGRATIONS==CONfIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status)
{
    Std_ReturnType ret = E_OK;
    if((port > PORT_MAX_NUMBER-1) || (NULL == direction_status))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = *tris_registers[port];
    }
    return ret;    
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGRATIONS==CONfIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic)
{
    Std_ReturnType ret = E_OK;
    if((port > PORT_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] = logic;
    }
    return ret;    
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGRATIONS==CONfIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic)
{
    Std_ReturnType ret = E_OK;
    if((port > PORT_MAX_NUMBER-1) || (NULL == logic))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = *port_registers[port];
    }
    return ret;    
}
#endif

/**
 * 
 * @param port
 * @return 
 */
#if GPIO_PORT_CONFIGRATIONS==CONfIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    Std_ReturnType ret = E_OK;
if((port > PORT_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] =  *lat_registers[port] ^ (0xFF);
    }
    return ret;    
}
#endif

