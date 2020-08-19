/*
 * File:   LCD.c
 * Author: MDTECHNOLOGY <www.mdtechnology.com.ec>
 *
 * Created on 6 de agosto de 2020, 8:59
 */


/*
 * PARA DESARROLLAR LA APLICACION COPIA LA FUNCION QUE REQUIERAS
 * 
 * LAS LIBRERIAS LCD.C Y LCD.H FUERON DESARROLLADAS EN EL
 * LABORATORIO DE MDTECHNOLOGY LOCALIZADO EN LA CIUDAD DE QUITO-ECUADOR
 * NO NOS RESPONSABILIZAMOS DEL MAL USO QUE SE REALICE.
 * 
 * RECOMENDADO PARA USOS ACADÉMICOS
 * 
 * 
 * FUNCIONES:
    void LCD_Initialize(void);
    void LCD_Control(char control_word);
    void LCD_Data(char data); 
    void LCD_Clear(void);
    void LCD_Cursor_Home(void);
    void LCD_Print(char* data);
    void LCD_Print_X_Y(int x, int y, char*data);
    void LCD_Gotoxy(int x, int y);
    void LCD_Put_Caracter(char address, char caracter[]);
 *  
 */



//CONTROL - Output Pins
#define TRISRS     TRISBbits.TRISB4    //RB4 - Output
#define TRISR_nW   TRISBbits.TRISB6    //RB6 - Output
#define TRISEN     TRISAbits.TRISA5    //RA5 - Output 

//LCD -  Control Port
#define RS          LATBbits.LATB4      //PIN_LCD: RS
#define R_nW        LATBbits.LATB6      //PIN_LCD: RW
#define EN          LATAbits.LATA5      //PIN_LCD: EN 

//DATA -> Output Port

// SELECCIONAR EL REGISTRO PARA CONFIGURAR EL PUERTO QUE SE DESEA COMO SALIDA AL LCD
#define PORT_TRIS        TRISC         //PORTC - Output
#define PORT_TRIS_4bits   0x0F
#define LCD             LATC       

//CONTROL -> Configurations
#define CLEAR            0x01      // CLEAR
#define CURSOR_HOME       0x02      // HOME:
#define FUNCTION_SET      0x28      // FUNCTION SET:             4 Bits, 2 Lines - Character 5*8
#define DISPLAY_ON_OFF     0x0C      // DISPLAY ON/OFF CONTROL:   LCD_ON, Cursor_OFF, Blink_Cursor_OFF
#define ENTRY_MODE_SET     0x06      // ENTRY MODE SET: INCREMENT CURSOR
#define LCD_LEFT_SHIFTH    0X18     // LCD_LEFT_SHIFTH
#define LCD_RIGHT_SHIFTH   0X1C     // LCD_LEFT_SHIFTH







//Instructions
void LCD_Initialize(void);
void LCD_Control(char control_word);
void LCD_Data(char data); 
void LCD_Clear(void);
void LCD_Cursor_Home(void);
void LCD_Print(char* data);
void LCD_Print_X_Y(int x, int y, char*data);
void LCD_Gotoxy(int x, int y);
void LCD_Put_Caracter(char address, char caracter[]);
void LCD_Time_Control(void);

