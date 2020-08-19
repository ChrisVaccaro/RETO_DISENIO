#include <xc.h>
#include <stdio.h>
#include "mcc_generated_files/mcc.h"
#include "LCD.h"

void updateLeds(void);
void setContador(uint8_t cont);
void setLimites(uint8_t max, uint8_t min);
void displayLimitsLCD(void);