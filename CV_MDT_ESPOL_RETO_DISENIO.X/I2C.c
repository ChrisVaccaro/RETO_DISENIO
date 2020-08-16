/*
 * File:   I2C.c
 * Author: MDTECHNOLOGY <www.mdtechnology.com.ec>
 *
 * Created on August 8, 2020, 1:02 AM
 */

#include "I2C.h"

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