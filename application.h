/* 
 * File:   application.h
 * Author: Yousab Gamal
 * Created on November 22, 2024, 4:19 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/******************Section: Includes**********************/
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/ADC/hal_adc.h"

/******************Section: Macros Declarations***********/

/******************Section: Macros Functions Declarations*/

/******************Section: Data Types Declarations*******/
extern chr_lcd_8bit_t lcd_2;
extern chr_lcd_4bit_t lcd_1;


/******************Section: Functions Declarations********/
void application_initializetion();

#endif	/* APPLICATION_H */

