/* 
 * File:   ecu_keypad.c
 * Author: yousg
 *
 * Created on February 27, 2025, 4:09 PM
 */

#include "ecu_keypad.h"

static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS]={
                                                                        {'7','8','9','/'},
                                                                        {'4','5','6','*'},
                                                                        {'1','2','3','-'},
                                                                        {'#','0','=','+'},
                                                                    };

/**
 * 
 * @param keypad_obj
 * @return 
 */
Std_ReturnType keypad_initialize(const keypad_t * keypad_obj)
{
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = 0,columns_counter = 0;
    if(NULL == keypad_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(rows_counter = 0;rows_counter < ECU_KEYPAD_ROWS ; rows_counter++)
        {
            ret = gpio_pin_intialize(&(keypad_obj->keypad_row_pins[rows_counter]));
        }
        for(columns_counter = 0;columns_counter < ECU_KEYPAD_COLUMNS ; columns_counter++)
        {
            ret = gpio_pin_direction_intialize(&(keypad_obj->keypad_columns_pins[columns_counter]));
        }
    }
    return ret;
}

/**
 * 
 * @param keypad_obj
 * @param value
 * @return 
 */
Std_ReturnType keypad_get_value(const keypad_t * keypad_obj , uint8 * value)
{
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = 0,columns_counter = 0,counter = 0;
    uint8 column_logic =0;
    if((NULL == keypad_obj) || (NULL == value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(rows_counter = 0;rows_counter < ECU_KEYPAD_ROWS ; rows_counter++)
        {
            for(counter = 0;counter < ECU_KEYPAD_ROWS ; counter++)
            {
                ret = gpio_pin_write_logic(&(keypad_obj->keypad_row_pins[counter]),GPIO_LOW);
            }
            gpio_pin_write_logic(&(keypad_obj->keypad_row_pins[rows_counter]),GPIO_HIGH);
            for(columns_counter = 0;columns_counter < ECU_KEYPAD_COLUMNS ; columns_counter++)
            {
                ret = gpio_pin_read_logic(&(keypad_obj->keypad_columns_pins[columns_counter]),&column_logic);
                if(GPIO_HIGH == column_logic)
                {
                    *value = btn_values[rows_counter][columns_counter];
                }
            }
        }
    }
    return ret;
}