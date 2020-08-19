/*
 * File:   LCD.c
 * Author: MDTECHNOLOGY <www.mdtechnology.com.ec>
 *
 * Created on 6 de agosto de 2020, 8:59
 */


#include <xc.h>
#include "LCD.h"
#define _XTAL_FREQ 32000000


void LCD_Initialize(void) {
    
   
    TRISRS = 0;         
    TRISEN = 0;
    TRISR_nW=0;
    PORT_TRIS = PORT_TRIS_4bits; 
    RS = 0;            
    EN = 0;
    R_nW=0;
    LCD = 0;
    
    /*
     * LCD Configuration
     */
    __delay_ms(50);    //Delay 
    
   
    LCD_Control(CLEAR);     
    LCD_Control(CURSOR_HOME);    
    LCD_Control(FUNCTION_SET);
    LCD_Control(DISPLAY_ON_OFF);      
    LCD_Control(ENTRY_MODE_SET);           
    return; 
}


void LCD_Control(char control_word) {
    RS = 0;
    R_nW=0;
    
            LCD = control_word & 0xF0;
            LCD_Time_Control();
            LCD = ((control_word & 0x0F) << 4);
            LCD_Time_Control();
           
    
    __delay_ms(2);
    return;
}


void LCD_Data(char data) {
    RS = 1;
    R_nW=0;
    
            LCD = data & 0xF0;
            LCD_Time_Control();
            LCD = ((data & 0x0F) << 4);
            LCD_Time_Control();
    
    __delay_us(50);
    return;
}


void LCD_Clear(void) {
    LCD_Control(CLEAR);
    return;
}


void LCD_Cursor_Home(void) {
    LCD_Control(CURSOR_HOME);
    return;
}


void LCD_Print(char *data) {
    while (*data)       
    {
        LCD_Data(*data); 
        data++; 
    }
    return;
}


void LCD_Print_X_Y(int x, int y, char *data) {
    char position;
    switch (y) 
    {
        case 0: 
            position = 0x80 + x;
            break;
        case 1: 
            position = 0xC0 + x;
            break;
        default: 
            position = 0x80 + x;
            break;
    }
    LCD_Control(position);
    LCD_Print(data);
    return;
}


void LCD_Gotoxy(int x, int y) {
    char position;
    switch (y) 
    {
        case 0: 
            position = 0x80 + x;
            break;
        case 1: 
            position = 0xC0 + x;
            break;
        default: 
            position = 0x80 + x;
            break;
    }
    LCD_Control(position);
    return;
}


/*
 *  Save char in CGRAM
 */
void LCD_Put_Caracter(char adress, char caracter[]) {
    int i;
    LCD_Control(0x40 + (adress * 8));
    for (i = 0; i < 8; i++) {
        LCD_Data(caracter[i]);
    }
    return;
}

void LCD_Time_Control(void) {
    EN = 1;
    __delay_us(5);
    EN = 0;
    __delay_us(5);
    return;
}
