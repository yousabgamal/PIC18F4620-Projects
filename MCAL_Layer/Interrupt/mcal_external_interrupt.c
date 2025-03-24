/* 
 * File:   mcal_external_interrupt.c
 * Author: yousg
 *
 * Created on March 10, 2025, 4:57 PM
 */
#include "mcal_external_interrupt.h"

/*pointer to functions*/
static void(*INT0_InterruptHandler)(void) = NULL;
static void(*INT1_InterruptHandler)(void) = NULL;
static void(*INT2_InterruptHandler)(void) = NULL;

static void(*RB4_InterruptHandlerHigh)(void) = NULL;
static void(*RB4_InterruptHandlerLow)(void) = NULL;
static void(*RB5_InterruptHandlerHigh)(void) = NULL;
static void(*RB5_InterruptHandlerLow)(void) = NULL;
static void(*RB6_InterruptHandlerHigh)(void) = NULL;
static void(*RB6_InterruptHandlerLow)(void) = NULL;
static void(*RB7_InterruptHandlerHigh)(void) = NULL;
static void(*RB7_InterruptHandlerLow)(void) = NULL;

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler));
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler));
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);


/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = 0;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*disable the external interrupt*/
        ret = Interrupt_INTx_Disable(int_obj);
        /*clear interrupt flag*/
        ret |= Interrupt_INTx_Clear_Flag(int_obj);
        /*configure interrupt edge*/
        ret |= Interrupt_INTx_Edge_Init(int_obj);
        /*configure interrupt I/O pin*/
        ret |= Interrupt_INTx_Pin_Init(int_obj);
        /*configure interrupt callback*/
        ret |= Interrupt_INTx_SetInterruptHandler(int_obj);
        /*enable the external interrupt*/
        ret |= Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}

void INT0_ISR(void)
{
    /*INT0 interrupt occurred(must be cleared)*/
    EXT_INT0_InterruptFlagClear();
    /*code*/
    
    /*callback function*/
    if(INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
}

void INT1_ISR(void)
{
    /*INT1 interrupt occurred(must be cleared)*/
    EXT_INT1_InterruptFlagClear();
    /*code*/
    
    /*callback function*/
    if(INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
}

void INT2_ISR(void)
{
    /*INT2 interrupt occurred(must be cleared)*/
    EXT_INT2_InterruptFlagClear();
    /*code*/
    
    /*callback function*/
    if(INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
}

void RB4_ISR(uint8 RB4_Source)
{
    /*RB4 interrupt occurred(must be cleared)*/
    EXT_RBx_InterrupFlagtClear();
    /*code*/
    
    /*callback function*/
    if(0 == RB4_Source)
    {
        if(RB4_InterruptHandlerHigh)
        {
            RB4_InterruptHandlerHigh();
        }
        else
        {
            /*Nothing*/
        }
    }
    else
    {
        if(RB4_InterruptHandlerLow)
        {
            RB4_InterruptHandlerLow();
        }
        else
        {
            /*Nothing*/
        }
    }
    
}

void RB5_ISR(uint8 RB5_Source)
{
    /*RB5 interrupt occurred(must be cleared)*/
    EXT_RBx_InterrupFlagtClear();
    /*code*/
    
    /*callback function*/
    if(0 == RB5_Source)
    {
        if(RB5_InterruptHandlerHigh)
        {
            RB5_InterruptHandlerHigh();
        }
        else
        {
            /*Nothing*/
        }
    }
    else 
    {
        if(RB5_InterruptHandlerLow)
        {
            RB5_InterruptHandlerLow();
        }
        else
        {
            /*Nothing*/
        }
    }
}

void RB6_ISR(uint8 RB6_Source)
{
    /*RB6 interrupt occurred(must be cleared)*/
    EXT_RBx_InterrupFlagtClear();
    /*code*/
    
    /*callback function*/
    if(0 == RB6_Source)
    {
        if(RB6_InterruptHandlerHigh)
        {
            RB6_InterruptHandlerHigh();
        }
        else
        {
            /*Nothing*/
        }
    }
    else
    {
        if(RB6_InterruptHandlerLow)
        {
            RB6_InterruptHandlerLow();
        }
        else
        {
            /*Nothing*/
        }
    }
}

void RB7_ISR(uint8 RB7_Source)
{
    /*RB7 interrupt occurred(must be cleared)*/
    EXT_RBx_InterrupFlagtClear();
    /*code*/
    
    /*callback function*/
    if(0 == RB7_Source)
    {
        if(RB7_InterruptHandlerHigh)
        {
            RB7_InterruptHandlerHigh();
        }
        else
        {
            /*Nothing*/
        }
    }
    else
    {
        if(RB7_InterruptHandlerLow)
        {
            RB7_InterruptHandlerLow();
        }
        else
        {
            /*Nothing*/
        }
    }
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EXT_RBx_InterruptDisable();
        EXT_RBx_InterrupFlagtClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                    EXT_RBx_HighPrioritySet();
                }
                else if(INTERRUPT_LOW_PRIORITY == int_obj->priority)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                    EXT_RBx_LowPrioritySet();
                }
                else
                {
                    /*Nothing*/
                }
        #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
        #endif
                ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
                switch(int_obj->mcu_pin.pin){
                    case GPIO_PIN4:
                        RB4_InterruptHandlerHigh = int_obj->EXT_InterruptHandlerHigh;
                        RB4_InterruptHandlerLow = int_obj->EXT_InterruptHandlerLow;
                        break;
                    case GPIO_PIN5:
                        RB5_InterruptHandlerHigh = int_obj->EXT_InterruptHandlerHigh;
                        RB5_InterruptHandlerLow = int_obj->EXT_InterruptHandlerLow;
                        break;
                    case GPIO_PIN6:
                        RB6_InterruptHandlerHigh = int_obj->EXT_InterruptHandlerHigh;
                        RB6_InterruptHandlerLow = int_obj->EXT_InterruptHandlerLow;
                        break;
                    case GPIO_PIN7:
                        RB7_InterruptHandlerHigh = int_obj->EXT_InterruptHandlerHigh;
                        RB7_InterruptHandlerLow = int_obj->EXT_InterruptHandlerLow;
                        break;
                    default:
                        ret = E_NOT_OK;
                        break;
                }
        EXT_RBx_InterruptEnable();
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj -> source)
        {
            case INTERRUPT_EXTERNAL_INT0:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else if(INTERRUPT_LOW_PRIORITY == int_obj->priority)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else
                {
                    /*Nothing*/
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT2:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                {
                   INTERRUPT_GlobalInterruptHighEnable();
                }
                else if(INTERRUPT_LOW_PRIORITY == int_obj->priority)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else
                {
                    /*Nothing*/
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_InterruptEnable();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj -> source)
        {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptDisable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptDisable();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptDisable();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj -> source)
        {
            case INTERRUPT_EXTERNAL_INT1:
                if(INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                {
                    EXT_INT1_HighPrioritySet();
                }
                else if(INTERRUPT_LOW_PRIORITY == int_obj->priority)
                {
                    EXT_INT1_LowPrioritySet();
                }
                else
                {
                    /*Nothing*/
                }
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if(INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                {
                    EXT_INT2_HighPrioritySet();
                }
                else if(INTERRUPT_LOW_PRIORITY == int_obj->priority)
                {
                    EXT_INT2_LowPrioritySet();
                }
                else
                {
                    /*Nothing*/
                }
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}
#endif 

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj -> source)
        {
            case INTERRUPT_EXTERNAL_INT0:
                if(INTERRUPT_RISING_EDGE == int_obj->edge)
                {
                    EXT_INT0_RisingEdgeSet();
                }
                else if(INTERRUPT_FALLING_EDGE == int_obj->edge)
                {
                    EXT_INT0_FallingEdgeSet();
                }
                else
                {
                    /*Nothing*/
                }
                break;
            case INTERRUPT_EXTERNAL_INT1:
                if(INTERRUPT_RISING_EDGE == int_obj->edge)
                {
                    EXT_INT1_RisingEdgeSet();
                }
                else if(INTERRUPT_FALLING_EDGE == int_obj->edge)
                {
                    EXT_INT1_FallingEdgeSet();
                }
                else
                {
                    /*Nothing*/
                }
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if(INTERRUPT_RISING_EDGE == int_obj->edge)
                {
                    EXT_INT2_RisingEdgeSet();
                }
                else if(INTERRUPT_FALLING_EDGE == int_obj->edge)
                {
                    EXT_INT2_FallingEdgeSet();
                }
                else
                {
                    /*Nothing*/
                }
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptFlagClear();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler))
{
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler))
{
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler))
{
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0:
                INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1:
                INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT2:
                INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}
