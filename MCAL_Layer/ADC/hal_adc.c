/* 
 * File:   hal_adc.c
 * Author: yousg
 *
 * Created on March 16, 2025, 5:01 PM
 */

#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(*ADC_InterruptHandler)(void) = NULL;
#endif
    
static inline void adc_input_channel_port_config( adc_channel_select_t channel);
static inline void select_result_format(const adc_conf_t *_adc);
static inline void configure_voltage_ref(const adc_conf_t *_adc);

/**
 * 
 * @param _adc
 * @return 
 */
Std_ReturnType ADC_Init(const adc_conf_t *_adc)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*Disable the ADC*/
        ADC_CONVERTER_DISABLE();
        /*Configure the acquisition time*/
        ADCON2bits.ACQT = _adc->aquizition_time;
        /*Configure the conversion clock*/
        ADCON2bits.ADCS = _adc->conversion_clock;
        /*Configure the default channel*/
        ADCON0bits.CHS = _adc->adc_channel;
        adc_input_channel_port_config(_adc->adc_channel);
        /*Configure the interrupt*/
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY == _adc->priority)
        {
            ADC_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _adc->priority)
        {
            ADC_LowPrioritySet();
        }
        else
        {
            /*Nothing*/
        }
        #endif
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;
        #endif
        /*Configure the result format*/
        select_result_format(_adc);
        /*Configure the voltage reference*/
        configure_voltage_ref(_adc);
        /*Enable the ADC*/
        ADC_CONVERTER_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @return 
 */
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*Disable the ADC*/
        ADC_CONVERTER_DISABLE();
        /*Configure the interrupt*/
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_InterruptDisable();
        #endif
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param channel
 * @return 
 */
Std_ReturnType ADC_SelectChannel(const adc_conf_t *_adc , adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*Configure the default channel*/
        ADCON0bits.CHS = channel;
        adc_input_channel_port_config(channel);
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @return 
 */
Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_START_CONVERSION();
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param conversion_status
 *        true - If conversion is complete
 *        false - If conversion is not complete
 * @return 
 */
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc , uint8 *conversion_status)
{
    Std_ReturnType ret = E_OK;
    if((NULL == _adc) || (NULL == conversion_status))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *conversion_status = (uint8)(!ADCON0bits.GO_nDONE);
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param conversion_result
 * @return 
 */
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc , uint16 *conversion_result)
{
    Std_ReturnType ret = E_OK;
    if((NULL == _adc) || (NULL == conversion_result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(ADC_RESULT_RIGHT == _adc->result_format)
        {
            *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_RESULT_LEFT == _adc->result_format)
        {
            *conversion_result = (uint16)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else
        {
            *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param channel
 * @param conversion_status
 * @return 
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc , adc_channel_select_t channel ,
                                 uint16 *conversion_status)
{
    Std_ReturnType ret = E_OK;
    if((NULL == _adc) || (NULL == conversion_status))
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*Select channel*/
        ret = ADC_SelectChannel(_adc , channel);
        /*Start ADC conversion*/
        ret = ADC_StartConversion(_adc);
        /*Check if conversion is completed*/
        while(ADCON0bits.GO_nDONE);//Blocking
        ret = ADC_GetConversionResult(_adc , conversion_status);
        
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param channel
 * @param conversion_status
 * @return 
 */
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc , adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*Select channel*/
        ret = ADC_SelectChannel(_adc , channel);
        /*Start ADC conversion*/
        ret = ADC_StartConversion(_adc);
    }
    return ret;
}
static inline void adc_input_channel_port_config(adc_channel_select_t channel)
{
    switch(channel)
    {
        case ADC_CHANNEL_AN0:
            SET_BIT(TRISA , _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1:
            SET_BIT(TRISA , _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_AN2:
            SET_BIT(TRISA , _TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_AN3:
            SET_BIT(TRISA , _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_AN4:
            SET_BIT(TRISA , _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_AN5:
            SET_BIT(TRISA , _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_AN6:
            SET_BIT(TRISA , _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_AN7:
            SET_BIT(TRISA , _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_AN8:
            SET_BIT(TRISA , _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_AN9:
            SET_BIT(TRISA , _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_AN10:
            SET_BIT(TRISA , _TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_AN11:
            SET_BIT(TRISA , _TRISB_RB4_POSN);
            break;
        case ADC_CHANNEL_AN12:
            SET_BIT(TRISA , _TRISB_RB0_POSN);
            break;     
    }
}

static inline void select_result_format(const adc_conf_t *_adc)
{
    if(ADC_RESULT_RIGHT == _adc->result_format)
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT == _adc->result_format)
    {
        ADC_RESULT_LEFT_FORMAT();
    }
    else
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
}

static inline void configure_voltage_ref(const adc_conf_t *_adc)
{
    if(ADC_VOLTAGE_REFERENCE_ENABLE == _adc->voltage_ref)
    {
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if(ADC_VOLTAGE_REFERENCE_DISABLE == _adc->voltage_ref)
    {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else
    {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
}

void ADC_ISR(void)
{
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
}