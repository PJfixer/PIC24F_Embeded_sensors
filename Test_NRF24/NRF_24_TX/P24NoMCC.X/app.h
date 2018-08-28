/* 
 * File:   app.h
 * Author: pierre
 *
 * Created on February 8, 2018, 1:21 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#define _XTAL_FREQ  32000000UL
#define FCY 16000000UL
#include <libpic30.h>
#include "uart.h"
#include "I2CA.h"
#include "PCA8574_lcd.h"
#include "spi1.h"
#include "RotaryEnc.h"
#include "bme280.h"
#include "24LC256.h"

union Word            //Setup a Union
{
  unsigned int IntVar;
  unsigned char Bytes[2];
};


void SYSTEM_Initialize(void);
void OSCILLATOR_Initialize(void);
void PIN_MANAGER_Initialize(void);





