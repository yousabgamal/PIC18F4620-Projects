/* 
 * File:   hal_gpio.h
 * Author: Ibrahim Shenouda
 *
 * Created on November 22, 2024, 3:35 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H


/******************Section: Includes**********************/
//#include "../pic18_chip_select.h"
//#include <pic18f4620.h>
//#include"./pic18f4620.h"               /*xc.h better than include pic standalone because xc.h include all pic versions and updates*/
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/device_config.h"
#include "hal_gpio_cfg.h"

/******************Section: Macros Declarations***********/

#define TRISA_REG        HWREG8(0xF92)  
#define TRISB_REG        HWREG8(0xF93)  
#define TRISC_REG        HWREG8(0xF94)  
#define TRISD_REG        HWREG8(0xF95)  
#define TRISE_REG        HWREG8(0xF96)  

#define LATA_REG         HWREG8(0xF89)  
#define LATB_REG         HWREG8(0xF8A)  
#define LATC_REG         HWREG8(0xF8B)  
#define LATD_REG         HWREG8(0xF8C)  
#define LATE_REG         HWREG8(0xF8D)

#define PORTA_REG        HWREG8(0xF80)  
#define PORTB_REG        HWREG8(0xF81)  
#define PORTC_REG        HWREG8(0xF82)  
#define PORTD_REG        HWREG8(0xF83)  
#define PORTE_REG        HWREG8(0xF84)

#define BIT_MASK                      (uint8)0x01
#define PORT_PIN_MAX_NUMBER           8
#define PORT_MAX_NUMBER               5
#define GPIO_PORT_PIN_CONFIGRATIONS   CONfIG_ENABLE
#define GPIO_PORT_CONFIGRATIONS       CONfIG_ENABLE

/******************Section: Macros Functions Declarations*/
#define HWREG8(_X)      (*((volatile uint8 *)(_X)))

#define SET_BIT(REG, BIT_BOSN)         (REG |= (BIT_MASK<< BIT_BOSN))
#define CLEAR_BIT(REG, BIT_BOSN)       (REG &= ~(BIT_MASK<< BIT_BOSN))
#define TOGGLE_BIT(REG, BIT_BOSN)      (REG ^= (BIT_MASK<< BIT_BOSN))
#define READ_BIT(REG, BIT_BOSN)        ((REG >> BIT_BOSN)& BIT_MASK)

/******************Section: Data Types Declarations*******/
typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum{
    GPIO_PIN0 = 0,
    GPIO_PIN1 = 1,
    GPIO_PIN2 = 2,
    GPIO_PIN3 = 3,
    GPIO_PIN4 = 4,
    GPIO_PIN5 = 5,
    GPIO_PIN6 = 6,
    GPIO_PIN7 = 7       
}pin_index_t;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX        
}port_index_t;

typedef struct{
    uint8 port : 3;      /*@ref: port_index_t */
    uint8 pin : 3;       /*@ref: pin_index_t */
    uint8 direction : 1; /*@ref: direction_t */
    uint8 logic : 1;     /*@ref: logic_t */
}pin_config_t;
/******************Section: Functions Declarations********/

Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config);

Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);



#endif	/* HAL_GPIO_H */

