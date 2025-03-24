/* 
 * File:   ecu_relay.h
 * Author: yousg
 *
 * Created on December 9, 2024, 6:38 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/******************Section: Includes**********************/
#include "ecu_relay_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/******************Section: Macros Declarations***********/
#define RELAY_ON_STATUS  0x01U
#define RELAY_OFF_STATUS 0x00U

/******************Section: Macros Functions Declarations*/

/******************Section: Data Types Declarations*******/
typedef struct {
    uint8 relay_port: 4;
    uint8 relay_pin: 3;
    uint8 relay_staus: 1;
}relay_t;

/******************Section: Functions Declarations********/
Std_ReturnType relay_initialize(const relay_t * _relay);
Std_ReturnType relay_turn_on(const relay_t * _relay);
Std_ReturnType relay_turn_off(const relay_t * _relay);

#endif	/* ECU_RELAY_H */

