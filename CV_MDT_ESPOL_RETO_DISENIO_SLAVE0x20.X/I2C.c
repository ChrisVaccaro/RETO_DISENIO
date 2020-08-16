/*
 * File:   I2C.c
 * Author: MDTECHNOLOGY <www.mdtechnology.com.ec>
 *
 * Created on August 8, 2020, 1:02 AM
 */

#include "I2C.h"

bool newData = false;
uint8_t dataSlave=0;

void I2C_Initialize(void){
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA4 = 1;  
    
    SSPDATPPS = 0X04;   //RA4->MSSP:SDA;    
    RA4PPS = 0X11;   //RA4->MSSP:SDA;    
    RA2PPS = 0X10;   //RA2->MSSP:SCL;    
    SSPCLKPPS = 0X02 ;   //RA2->MSSP:SCL;    
    
    return;
}

void I2C_Master_Initialize(void){
    SSP1STAT = 0x80;
    SSP1CON1 = 0x08;
    SSP1CON2 = 0x00;
    SSP1CON3 = 0x00; 
    SSP1ADD = (uint8_t)((_XTAL_FREQ/(4*I2C_bps))-1);
    
    SSP1CON1bits.SSPEN = 1; 
    
    return; 
}

void I2C_Slave_Initialize(short address){
    SSP1STAT        = 0x80;
    SSP1CON1        = 0x26;
    SSP1CON2        = 0x00;
    SSP1CON3        = 0x00; 
    SSP1ADD         = address;
    PIR1bits.SSP1IF = 0;
    PIE1bits.SSP1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    return;
}

void I2C_Start(void){
    while(SSP1STATbits.R_nW || SSP1CON2&0x1F);
    SSP1CON2bits.SEN= 1;
    
    return;
}

void I2C_Restart(void){
    while(SSP1STATbits.R_nW || SSP1CON2&0x1F);
    SSP1CON2bits.RSEN = 1;
    
    return;
}

void I2C_Stop(void){
    while(SSP1STATbits.R_nW || SSP1CON2&0x1F);
    SSP1CON2bits.PEN = 1;
    
    return;
}

void I2C_ACK(void){
    SSP1CON2bits.ACKDT = 0; 
    SSP1CON2bits.ACKEN = 1; 
    while (SSP1CON2bits.ACKEN); 
    
    return;
}

void I2C_NACK(void){
    SSP1CON2bits.ACKDT = 1; 
    SSP1CON2bits.ACKEN = 1; 
    while (SSP1CON2bits.ACKEN); 
    
    return;
}

void I2C_Write(uint8_t data){
    while(SSP1STATbits.R_nW || SSP1CON2&0x1F);
    SSP1BUF = data;

    return;
}

uint8_t I2C_Read(void){
    uint8_t data_rx     = 0x00;
    while(SSP1STATbits.R_nW || SSP1CON2&0x1F);
    SSP1CON2bits.RCEN   = 1;
    while(SSP1STATbits.R_nW || SSP1CON2&0x1F);
    data_rx             = SSP1BUF;
    SSP1CON2bits.ACKDT  = 1;
    SSP1CON2bits.ACKEN  = 1;
    
    return data_rx;
}

void I2C_Slave_ISR(void){
    SSPCON1bits.CKP = 0;
    
    if(SSPCON1bits.SSPOV || SSPCON1bits.WCOL){//Si hay desborde o colision
        uint8_t valor = SSP1BUF; //limpiar el buffer
        SSPCON1bits.SSPOV = 0;
        SSPCON1bits.WCOL = 0;
        SSPCON1bits.CKP = 1;
    }
    
    if(!SSP1STATbits.D_nA && !SSP1STATbits.R_nW){//address+write
        uint8_t valor = SSP1BUF; //limpiar el buffer(address)
        while(!SSP1STATbits.BF);
        dataSlave = SSP1BUF;
        newData = true;
        SSPCON1bits.CKP = 1;
    }
    else if(!SSP1STATbits.D_nA && SSP1STATbits.R_nW){//address+read
        uint8_t valor = SSP1BUF; //limpiar el buffer(address)
        SSP1STATbits.BF = 0;
        SSP1BUF = 0;
        SSPCON1bits.CKP = 1;
        while(SSP1STATbits.BF);
    }
    PIR1bits.SSP1IF = 0;
}

bool I2C_isDataReady(void){
    return newData;
}

uint8_t I2C_getDataSlave(void){
    newData = false;
    return dataSlave;
}