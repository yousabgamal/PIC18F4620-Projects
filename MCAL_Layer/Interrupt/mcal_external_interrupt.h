/* 
 * File:   mcal_external_interrupt.h
 * Author: yousg
 *
 * Created on March 10, 2025, 4:56 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/******************Section: Includes**********************/
#include "mcal_interrupt_cfg.h"

/******************Section: Macros Declarations***********/
#if EXTERNAL_INTERRUPT_INTx_FEATUER_ENABLE == INTERRUPT_FEATURE_ENABLE

/******************************INT0***************************************/
/*sets the interrupt enable for the external interrupt, INT0*/
#define EXT_INT0_InterruptEnable()       (INTCONbits.INT0IE = 1)
/*clear the interrupt enable for the external interrupt, INT0*/
#define EXT_INT0_InterruptDisable()      (INTCONbits.INT0IE = 0)
/*clear the interrupt flag for the external interrupt, INT0*/
#define EXT_INT0_InterruptFlagClear()    (INTCONbits.INT0IF = 0)
/*sets the edge detect of the extern interrupt to negative edge*/
#define EXT_INT0_RisingEdgeSet()         (INTCON2bits.INTEDG0 = 1)
/*sets the edge detect of the extern interrupt to negative edge*/
#define EXT_INT0_FallingEdgeSet()        (INTCON2bits.INTEDG0 = 0)

/******************************INT1***************************************/
/*sets the interrupt enable for the external interrupt, INT1*/
#define EXT_INT1_InterruptEnable()       (INTCON3bits.INT1IE = 1)
/*clear the interrupt enable for the external interrupt, INT1*/
#define EXT_INT1_InterruptDisable()      (INTCON3bits.INT1IE = 0)
/*clear the interrupt flag for the external interrupt, INT1*/
#define EXT_INT1_InterruptFlagClear()    (INTCON3bits.INT1IF = 0)
/*sets the edge detect of the extern interrupt to negative edge*/
#define EXT_INT1_RisingEdgeSet()         (INTCON2bits.INTEDG1 = 1)
/*sets the edge detect of the extern interrupt to negative edge*/
#define EXT_INT1_FallingEdgeSet()        (INTCON2bits.INTEDG1 = 0)

/******************************INT2***************************************/
/*sets the interrupt enable for the external interrupt, INT2*/
#define EXT_INT2_InterruptEnable()       (INTCON3bits.INT2IE = 1)
/*clear the interrupt enable for the external interrupt, INT2*/
#define EXT_INT2_InterruptDisable()      (INTCON3bits.INT2IE = 0)
/*clear the interrupt flag for the external interrupt, INT2*/
#define EXT_INT2_InterruptFlagClear()    (INTCON3bits.INT2IF = 0)
/*sets the edge detect of the extern interrupt to negative edge*/
#define EXT_INT2_RisingEdgeSet()         (INTCON2bits.INTEDG2 = 1)
/*sets the edge detect of the extern interrupt to negative edge*/
#define EXT_INT2_FallingEdgeSet()        (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/*set the INT1 external interrupt priority to high*/
#define EXT_INT1_HighPrioritySet()  (INTCON3bits.INT1IP = 1)
/*set the INT1 external interrupt priority to low*/
#define EXT_INT1_LowPrioritySet()   (INTCON3bits.INT1IP = 0)
/*set the INT2 external interrupt priority to high*/
#define EXT_INT2_HighPrioritySet()  (INTCON3bits.INT2IP = 1)
/*set the INT2 external interrupt priority to low*/
#define EXT_INT2_LowPrioritySet()   (INTCON3bits.INT2IP = 0)

#endif 

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATUER_ENABLE == INTERRUPT_FEATURE_ENABLE

/*sets the interrupt enable for the external interrupt, RBx*/
#define EXT_RBx_InterruptEnable()       (INTCONbits.RBIE = 1)
/*clear the interrupt enable for the external interrupt, RBx*/
#define EXT_RBx_InterruptDisable()      (INTCONbits.RBIE = 0)
/*clear the interrupt flag for the external interrupt, RBx*/
#define EXT_RBx_InterrupFlagtClear()    (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/*set the RBx external interrupt priority to high*/
#define EXT_RBx_HighPrioritySet()  (INTCON2bits.RBIP = 1)
/*set the RBx external interrupt priority to low*/
#define EXT_RBx_LowPrioritySet()   (INTCON2bits.RBIP = 0)

#endif

#endif

/******************Section: Macros Functions Declarations*/

/******************Section: Data Types Declarations*******/
typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE,
}interrupt_INTx_edge;

typedef enum{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2,
}interrupt_INTx_src;

typedef struct {
    pin_config_t mcu_pin;
    void (* EXT_InterruptHandler)(void);
    interrupt_INTx_edge edge;
    interrupt_INTx_src source;
    interrupt_priority_cfg priority;
}interrupt_INTx_t;

typedef struct {
    void (* EXT_InterruptHandlerHigh)(void);
    void (* EXT_InterruptHandlerLow)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_t;

/******************Section: Functions Declarations********/
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

