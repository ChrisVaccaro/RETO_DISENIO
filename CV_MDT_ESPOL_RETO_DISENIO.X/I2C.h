#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
/*
 * PARA DESARROLLAR LA APLICACION COPIA LA FUNCION QUE REQUIERAS
 * 
 * LAS LIBRERIAS I2C.C Y I2C.H FUERON DESARROLLADAS EN EL
 * LABORATORIO DE MDTECHNOLOGY LOCALIZADO EN LA CIUDAD DE QUITO-ECUADOR
 * NO NOS RESPONSABILIZAMOS DEL MAL USO QUE SE REALICE.
 * 
 * RECOMENDADO PARA USOS ACADÉMICOS
 * 
 * 
 * FUNCIONES:
        void I2C_Initialize(void);
        void I2C_Master_Initialize(void);
        void I2C_Slave_Initialize(void);
        void I2C_Start(void);
        void I2C_Restart(void);
        void I2C_Stop(void);
        void I2C_ACK(void);
        void I2C_NACK(void);
        void I2C_Write(uint8_t data);
        uint8_t I2C_Read(void);
 *  
 */

#define I2C_bps            100000
#define _XTAL_FREQ       32000000

void I2C_Initialize(void);
void I2C_Master_Initialize(void);
void I2C_Slave_Initialize(short address);
void I2C_Start(void);
void I2C_Restart(void);
void I2C_Stop(void);
void I2C_ACK(void);
void I2C_NACK(void);
void I2C_Write(uint8_t data);
uint8_t I2C_Read(void);

void I2C_Slave_ISR(void);