/* 
 * File:   mcal_internal_interrupt.h
 * Author: yousg
 *
 * Created on March 10, 2025, 4:56 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H


/******************Section: Includes**********************/
#include "mcal_interrupt_cfg.h"

/******************Section: Macros Declarations***********/

/******************Section: Macros Functions Declarations*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /*Clear the interrupt enable for the ADC module*/
    #define ADC_InterruptDisable()      (PIE1bits.ADIE = 0)
    /*Sets the interrupt enable for the ADC module*/
    #define ADC_InterruptEnable()       (PIE1bits.ADIE = 1)
    /*Clear interrupt flag for the ADC module*/
    #define ADC_InterruptFlagClear()    (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    /*Set ADC interrupt priority to high*/
    #define ADC_HighPrioritySet()       (IPR1bits.ADIP = 1)
    /*Set ADC interrupt priority to low*/
    #define ADC_LowPrioritySet()        (IPR1bits.ADIP  = 0)
#endif
#endif
/******************Section: Data Types Declarations*******/

/******************Section: Functions Declarations********/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

