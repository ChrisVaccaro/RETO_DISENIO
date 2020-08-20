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
 * Funciones para UART
 */
void almacenarTexto(bool cifrado){
    uint8_t etapa_act = etapa;
    while(EUSART_DataReady){
        caracter = EUSART_Read(cifrado);
        if(caracter!='\r' && caracter!='\n' && i<MAX_SIZE-1)input[i++]=caracter;
        else{
            input[i]=0;
            etapa = etapa_act + 1;
           //No se hace "etapa++", porque se puede recibir \r\n consecutivamente
           //y "etapa" se incrementaría dos veces
        }
    }
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

void interfaz(void){
    switch(etapa){
        case 0:
            printf("\r\n\r\n");
            printf("==============================\r\n");
            printf("===     RETO MDT-ESPOL     ===\r\n");
            printf("=== CHRISTOPHER VACCARO C. ===\r\n");
            printf("==============================\r\n");
            
            etapa++;
            break;
        case 1:
            printf("\r\nIngrese el codigo de acceso: ");
            etapa++;
            break;
        case 2:
            almacenarTexto(true);
            break;
        case 3:
            i=0;
            if(strcmp(input,PASSWORD) == 0){
                printf("\r\n\r\nAcceso exitoso!!!");
                etapa++;
            }
            else etapa=1;
            break;
        case 4:
            printf("\r\n\r\nSeleccione un modo de acceso\r\n");
            printf("1. Modo opciones\r\n");
            printf("2. Modo comandos\r\n");
            printf("3. Salir\r\n");
            etapa++;
            break;
        case 5:
            printf("\r\nIngrese una opcion: ");
            etapa++;
            break;
        case 6:
            almacenarTexto(false);
            break;
        case 7:
            i=0;
            if(strcmp(input,"1") == 0) etapa = 8;
            else if(strcmp(input,"2") == 0) etapa = 20; /**********************************************/
            else if(strcmp(input,"3") == 0) etapa = 0;
            else etapa = 5;
            break;
        case 8:
            printf("\r\n\r\n");
            printf(" 1. Obtener contador               (Coordinador)\r\n");
            printf(" 2. Obtener estados DIPSwitch      (Disp 0x20)\r\n");
            printf(" 3. Obtener DIPSwitch activados    (Disp 0x20)\r\n");
            printf(" 4. Obtener DIPSwitch desactivados (Disp 0x20)\r\n");
            printf(" 5. Obtener estados especificos    (Disp 0x20)\r\n");
            printf(" 6. Obtener estado del SISTEMA     (Disp 0x30)\r\n");
            printf(" 7. Obtener alarmas configuradas   (Disp 0xA0)\r\n");
            printf(" 8. Configurar alarmas             (Disp 0xA0)\r\n");
            printf(" 9. Regresar al menu anterior\r\n");
            printf("10. Salir\r\n");
            etapa++;
            break;
        case 9:
            printf("\r\nIngrese una opcion: ");
            etapa++;
            break;
        case 10:
            almacenarTexto(false);
            break;
        case 11:
            i=0;
            if(strcmp(input,"1") == 0) etapa = 20;
            else if(strcmp(input,"2") == 0) etapa = 20;
            else if(strcmp(input,"3") == 0) etapa = 20;
            else if(strcmp(input,"4") == 0) etapa = 20;
            else if(strcmp(input,"5") == 0) etapa = 20;
            else if(strcmp(input,"6") == 0) etapa = 20;
            else if(strcmp(input,"7") == 0) etapa = 20;
            else if(strcmp(input,"8") == 0) etapa = 20;
            else if(strcmp(input,"9") == 0) etapa = 4;
            else if(strcmp(input,"10") == 0) etapa = 0;
            else etapa = 9;
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            break;
        case 15:
            break;
        case 16:
            break;
        case 17:
            break;
        case 18:
            break;
        default:
            break;
    }
}