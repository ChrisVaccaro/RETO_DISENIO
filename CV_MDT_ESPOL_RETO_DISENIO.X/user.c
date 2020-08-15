/*
 * File:   user.c
 * Author: Christopher Vaccaro
 *
 * Created on August 15, 2020, 12:14 PM
 */


#include <xc.h>
#include "user.h"

void WRITE_EEPROM_I2C(uint8_t address,uint16_t reg,uint8_t data) {
    
    I2C_Start();    
    I2C_Write(address);    
    I2C_Write((uint8_t)((reg&0xFF00)>>8));
    I2C_Write((uint8_t)((reg&0x00FF)));
    I2C_Write(data); 
    I2C_Stop();
    __delay_ms(100);
    
    return;
}

uint8_t READ_EEPROM_DATA(uint8_t address,uint16_t reg){
    uint8_t data;
    
    I2C_Start ();  
    I2C_Write (address);
    I2C_Write((uint8_t)((reg&0xFF00)>>8));
    I2C_Write((uint8_t)((reg&0x00FF)));  
    I2C_Restart(); 
    I2C_Write (address|1);
    data= I2C_Read();  
    I2C_Stop ();  
    __delay_ms (100); 
    
    return data; 
}