/* 
 * File:   ecu_keypad.h
 * Author: yousg
 *
 * Created on February 27, 2025, 4:09 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/******************Section: Includes**********************/
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/******************Section: Macros Declarations***********/
#define ECU_KEYPAD_ROWS    4
#define ECU_KEYPAD_COLUMNS 4

/******************Section: Macros Functions Declarations*/

/******************Section: Data Types Declarations*******/
typedef struct
{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/******************Section: Functions Declarations********/
Std_ReturnType keypad_initialize(const keypad_t * keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t * keypad_obj , uint8 * value);

#endif	/* ECU_KEYPAD_H */

