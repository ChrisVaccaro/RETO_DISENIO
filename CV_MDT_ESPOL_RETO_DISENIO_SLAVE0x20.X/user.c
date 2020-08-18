/*
 * File:   user.c
 * Author: Christopher Vaccaro
 *
 * Created on August 18, 2020, 12:31 PM
 */


#include <xc.h>
#include "user.h"

uint8_t contador = 0;
bool flag=false;
char DISPLAY[16] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};

void setCounter(uint8_t cont){
    contador = cont;
}
uint8_t getCounter(void){
    return contador;
}

void displayISR(void){
    LATBbits.LATB4=1;
    LATBbits.LATB6=1;
    
    if(flag){
        LATC = DISPLAY[contador%10];
        LATBbits.LATB4=1;
        LATBbits.LATB6=0;
    }
    else{
        LATC = DISPLAY[contador/10];
        LATBbits.LATB4=0;
        LATBbits.LATB6=1;
    }
    flag = ~flag;
}
