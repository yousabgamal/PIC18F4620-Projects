/* 
 * File:   mcal_interrupt_cfg.h
 * Author: yousg
 *
 * Created on March 10, 2025, 4:55 PM
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H

/******************Section: Includes**********************/
//#include <pic18f4620.h>
#include <xc.h>
#include "../pic18_chip_select.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/******************Section: Macros Declarations***********/
#define INTERRUPT_ENABLE              1
#define INTERRUPT_DISABLE             0
#define INTERRUPT_OCCUR               1
#define INTERRUPT_NOT_OCCUR           0
#define INTERRUPT_PRIORITY_ENABLE     1
#define INTERRUPT_PRIORITY_DISABLE    0

/******************Section: Macros Functions Declarations*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/*macro enable priority*/
#define INTERRUPT_PriorityLevelEnable()          (RCONbits.IPEN = 1)
/*macro disable priority*/
#define INTERRUPT_PriorityLevelDisable()         (RCONbits.IPEN = 0)

/*macro enable high priority global interrupts*/
#define INTERRUPT_GlobalInterruptHighEnable()    (INTCONbits.GIEH = 1)
/*macro disable high priority global interrupts*/
#define INTERRUPT_GlobalInterruptHighDisable()   (INTCONbits.GIEH = 0)

/*macro enable low priority global interrupts*/
#define INTERRUPT_GlobalInterruptLowEnable()     (INTCONbits.GIEL = 1)
/*macro disable low priority global interrupts*/
#define INTERRUPT_GlobalInterruptLowDisable()    (INTCONbits.GIEL = 0)

#else

/*macro enable global interrupts*/
#define INTERRUPT_GlobalInterruptEnable()        (INTCONbits.GIE = 1)
/*macro disable global interrupts*/
#define INTERRUPT_GlobalInterruptDisable()       (INTCONbits.GIE = 0)

/*macro enable peripheral interrupts*/
#define INTERRUPT_PeripheralInterruptEnable()    (INTCONbits.PEIE = 1)
/*macro disable peripheral interrupts*/
#define INTERRUPT_PeripheralInterruptDisable()   (INTCONbits.PEIE = 0)

#endif

/******************Section: Data Types Declarations*******/
typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY,
}interrupt_priority_cfg; 

/******************Section: Functions Declarations********/

#endif	/* MCAL_INTERRUPT_CFG_H */

