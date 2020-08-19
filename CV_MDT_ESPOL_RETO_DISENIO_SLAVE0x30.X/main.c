/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC16F1619
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#pragma warning disable 520,1498
#include "mcc_generated_files/mcc.h"
#include "I2C.h"

uint8_t max_limit = 0, min_limit = 0;
uint8_t contador;
uint16_t valori2c;
/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    I2C_Initialize();
    I2C_Slave_Initialize(0x30);
    
    while (1)
    {
        if(I2C_isDataReady()){
            valori2c = I2C_getDataSlave();
            if((valori2c&0xFF00) == 0xFF00){
                contador = valori2c;
                if(contador > max_limit || contador < min_limit){
                    IO_RB5_SetHigh();
                    IO_RB7_SetLow();
                }
                else{
                    IO_RB5_SetLow();
                    IO_RB7_SetHigh();
                }
            }
            else{
                max_limit = valori2c >> 8;
                min_limit = valori2c;
                
                if(contador > max_limit || contador < min_limit){
                    IO_RB5_SetHigh();
                    IO_RB7_SetLow();
                }
                else{
                    IO_RB5_SetLow();
                    IO_RB7_SetHigh();
                }
            }
        }
    }
}
/**
 End of File
*/