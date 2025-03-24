/* 
 * File:   hal_eeprom.h
 * Author: yousg
 *
 * Created on March 15, 2025, 2:54 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/******************Section: Includes**********************/
#include <xc.h>
#include "../pic18_chip_select.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"

/******************Section: Macros Declarations***********/
#define ACCESS_FLASH_PROGRAM_MEMORY          1
#define ACCESS_EEPROM_PROGRAM_MEMORY         0

#define ACCESS_CONFIG_REGESTERS              1
#define ACCESS_EEPROM_FLASH_MEMORY           0
 
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM      1
#define INHIBIT_WRITE_CYCLES_FLASH_EEPROM    0

#define INITIATE_DATA_EEPROM_WRITE_ERASE     1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED    0

#define INITIATE_DATA_EEPROM_READ            1

/******************Section: Macros Functions Declarations*/

/******************Section: Data Types Declarations*******/

/******************Section: Functions Declarations********/
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd , uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd , uint8 *bData);

#endif	/* HAL_EEPROM_H */

