/*
 * File:   User.c
 * Author: MDTECHNOLOGY <www.mdtechnology.com.ec>
 * Co-Author: Christopher Vaccaro
 * Created on August 6, 2020, 4:28 PM
 */

#include "User.h"

uint8_t contador=0;
uint8_t max_limit = 0, min_limit = 0;

void setContador(uint8_t cont){
    contador = cont;
}
void setLimites(uint8_t max, uint8_t min){
    max_limit = max;
    min_limit = min;
}
void updateLeds(void){
    if(contador > max_limit || contador < min_limit){
        IO_RB5_SetHigh();
        IO_RB7_SetLow();
    }
    else{
        IO_RB5_SetLow();
        IO_RB7_SetHigh();
    }
}

void displayLimitsLCD(void){
    char numeroStr[3]={0};
    sprintf(numeroStr,"%02d",min_limit);
    LCD_Print_X_Y(5,1,numeroStr);
    sprintf(numeroStr,"%02d",max_limit);
    LCD_Print_X_Y(13,1,numeroStr);
}