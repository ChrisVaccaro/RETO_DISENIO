/*
 * File:   user.c
 * Author: Christopher Vaccaro
 *
 * Created on August 15, 2020, 12:14 PM
 */


#include <xc.h>
#include "user.h"

uint8_t contador = 0;
bool change = false;

/*
 * Funciones para el contador
 */
void incCounter(void){
    contador = (contador>=99)?0:contador+1;
    change = true;
}
void decCounter(void){
    contador = (contador<=0)?99:contador-1;
    change = true;
}
uint8_t getCounter(void){
    change = false;
    return contador;
}
bool isChangeCounter(void){
    return change;
}

/*
 * Funciones para alarmas
 */
void alarms_Initialize(void){
    if(READ_EEPROM_DATA(ADDRESS_SLAVE_EEPROM,ADDRESS_EEPROM_EXT_INIT) != VALUE_EEPROM_EXT_INIT){
        WRITE_EEPROM_I2C(ADDRESS_SLAVE_EEPROM,ADDRESS_EEPROM_MIN,DEFAULT_MIN_VALUE);
        WRITE_EEPROM_I2C(ADDRESS_SLAVE_EEPROM,ADDRESS_EEPROM_MAX,DEFAULT_MAX_VALUE);
        WRITE_EEPROM_I2C(ADDRESS_SLAVE_EEPROM,ADDRESS_EEPROM_EXT_INIT,VALUE_EEPROM_EXT_INIT);
    }
    sendAlarmsI2C(ADDRESS_SLAVE2,READ_EEPROM_DATA(ADDRESS_SLAVE_EEPROM,ADDRESS_EEPROM_MIN),READ_EEPROM_DATA(ADDRESS_SLAVE_EEPROM,ADDRESS_EEPROM_MAX));
}
void sendAlarmsI2C(uint8_t address, uint8_t min, uint8_t max){
    uint16_t limits  = (max<<8)|(min);
    WRITE_SLAVE_I2C_16BITS(address,limits);
}

/*
 * Funciones para escritura/lectura EEPROM I2C
 */
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

/*
 * Funciones para escritura/lectura esclavos I2C
 */
void WRITE_SLAVE_I2C(uint8_t address,uint8_t data) {
    
    I2C_Start();    
    I2C_Write(address);
    I2C_Write(data); 
    I2C_Stop();
    __delay_ms(100);
    
    return;
}

void WRITE_SLAVE_I2C_16BITS(uint8_t address,uint16_t data){

    I2C_Start();    
    I2C_Write(address);
    I2C_Write(data>>8);
    I2C_Write(data);
    I2C_Stop();
    __delay_ms(100);
    
    return;
}

uint8_t READ_SLAVE_DATA(uint8_t address){
    uint8_t data;
    
    I2C_Start ();
    I2C_Write (address|1);
    data= I2C_Read();  
    I2C_Stop ();  
    __delay_ms (100); 
    
    return data; 
}