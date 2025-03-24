/* 
 * File:   hal_eeprom.c
 * Author: yousg
 *
 * Created on March 15, 2025, 2:54 PM
 */

#include "hal_eeprom.h"

/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd , uint8 bData)
{
    Std_ReturnType ret = E_OK;
    /*==========================WRITE STEPS=============================*/
    /*Read the interrupt status(enabled or disabled)*/
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    /*Update the address registers*/
    EEADRH = (uint8)((bAdd >> 8)&(0x03));
    EEADR = (uint8)(bAdd & 0xFF);
    /*Update the data register*/
    EEDATA = bData;
    /*Select access data EEPROM memory*/
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_EEPROM_FLASH_MEMORY;
    /*Allows write-cycles to flash program /data EEPROM*/
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
     /*Disable all interrupts(GIE)*/
    INTERRUPT_GlobalInterruptDisable();
    /*Write the required sequence: 0x55 -> 0xAA*/
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /*initialize data EEPROM erase/write cycle*/
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /*Wait for write to complete*/
    while(EECON1bits.WR);
    /*Inhibits(no access) write cycle to flash program/data EEPROM*/
    EECON1bits.WREN = INHIBIT_WRITE_CYCLES_FLASH_EEPROM;
    /*Restore the interrupt status(enabled or disabled)*/
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}

/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd , uint8 *bData)
{
    Std_ReturnType ret = E_OK;
    if(NULL == bData)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*==========================REAd STEPS=============================*/
        /*Update the address registers*/
        EEADRH = (uint8)((bAdd >> 8)&(0x03));
        EEADR = (uint8)(bAdd & 0xFF);
        /*Select access data EEPROM memory*/
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_EEPROM_FLASH_MEMORY;
        /*Initiates a data EEPROM read cycle*/
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP();//NO OPERATION
        NOP();//NO OPERATION
        /*Return data*/
        *bData = EEDATA;
    }
    return ret;
}
