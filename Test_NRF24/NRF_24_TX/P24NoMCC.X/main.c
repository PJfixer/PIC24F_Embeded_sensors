/* 
 * File:   main.c
 * Author: pierre
 *
 * Created on February 8, 2018, 1:21 PM
 */
// CONFIG4
#pragma config DSWDTPS = DSWDTPS1F    // Deep Sleep Watchdog Timer Postscale Select bits->1:68719476736 (25.7 Days)
#pragma config DSWDTOSC = LPRC    // DSWDT Reference Clock Select->DSWDT uses LPRC as reference clock
#pragma config DSBOREN = ON    // Deep Sleep BOR Enable bit->DSBOR Enabled
#pragma config DSWDTEN = ON    // Deep Sleep Watchdog Timer Enable->DSWDT Enabled
#pragma config DSSWEN = ON    // DSEN Bit Enable->Deep Sleep is controlled by the register bit DSEN
#pragma config PLLDIV = PLL4X    // USB 96 MHz PLL Prescaler Select bits->4x PLL selected
#pragma config I2C1SEL = DISABLE    // Alternate I2C1 enable bit->I2C1 uses SCL1 and SDA1 pins
#pragma config IOL1WAY = ON    // PPS IOLOCK Set Only Once Enable bit->Once set, the IOLOCK bit cannot be cleared

// CONFIG3
#pragma config WPFP = WPFP127    // Write Protection Flash Page Segment Boundary->Page 127 (0x1FC00)
#pragma config SOSCSEL = OFF    // SOSC Selection bits->Digital (SCLKI) mode
#pragma config WDTWIN = PS25_0    // Window Mode Watchdog Timer Window Width Select->Watch Dog Timer Window Width is 25 percent
#pragma config PLLSS = PLL_FRC    // PLL Secondary Selection Configuration bit->PLL is fed by the on-chip Fast RC (FRC) oscillator
#pragma config BOREN = ON    // Brown-out Reset Enable->Brown-out Reset Enable
#pragma config WPDIS = WPDIS    // Segment Write Protection Disable->Disabled
#pragma config WPCFG = WPCFGDIS    // Write Protect Configuration Page Select->Disabled
#pragma config WPEND = WPENDMEM    // Segment Write Protection End Page Select->Write Protect from WPFP to the last page of memory

// CONFIG2
#pragma config POSCMD = NONE    // Primary Oscillator Select->Primary Oscillator Disabled
#pragma config WDTCLK = LPRC    // WDT Clock Source Select bits->WDT uses LPRC
#pragma config OSCIOFCN = ON    // OSCO Pin Configuration->OSCO/CLKO/RA3 functions as port I/O (RA3)
#pragma config FCKSM = CSDCMD    // Clock Switching and Fail-Safe Clock Monitor Configuration bits->Clock switching and Fail-Safe Clock Monitor are disabled
#pragma config FNOSC = FRCPLL    // Initial Oscillator Select->Fast RC Oscillator with PLL module (FRCPLL)
#pragma config ALTCMPI = CxINC_RB    // Alternate Comparator Input bit->C1INC is on RB13, C2INC is on RB9 and C3INC is on RA0
#pragma config WDTCMX = WDTCLK    // WDT Clock Source Select bits->WDT clock source is determined by the WDTCLK Configuration bits
#pragma config IESO = ON    // Internal External Switchover->Enabled

// CONFIG1
#pragma config WDTPS = PS32768    // Watchdog Timer Postscaler Select->1:32768
#pragma config FWPSA = PR128    // WDT Prescaler Ratio Select->1:128
#pragma config WINDIS = OFF    // Windowed WDT Disable->Standard Watchdog Timer
#pragma config FWDTEN = OFF    // Watchdog Timer Enable->WDT disabled in hardware; SWDTEN bit disabled
#pragma config ICS = PGx1    // Emulator Pin Placement Select bits->Emulator functions are shared with PGEC1/PGED1
#pragma config LPCFG = OFF    // Low power regulator control->Disabled - regardless of RETEN
#pragma config GWRP = OFF    // General Segment Write Protect->Write to program memory allowed
#pragma config GCP = OFF    // General Segment Code Protect->Code protection is disabled
#pragma config JTAGEN = OFF    // JTAG Port Enable->Disabled



#include "app.h"

/*
                         Main application
 */
union Word lumos;


void ConvertFloattoLCDString(float FractionalNumber)
{
 unsigned char LCDBuffer[10] ;
 sprintf((char*)LCDBuffer,"%.2f",(double)FractionalNumber);
 lcd_str((char*)LCDBuffer) ;
}

int main(void)
{
 
    SYSTEM_Initialize();
    //SetupInteruptEncoder();
  /*  BME280_write8(BME280_REGISTER_CONTROLHUMID, 0x03); // regler avant  CONTROL !!!
    BME280_write8(BME280_REGISTER_CONTROL, 0b01101111);
    readSensorCoefficients();
    BME280_goForceMode(); */
   
   // float input = BME280_readTemperature();
    
    
   // LCDbegin(20,4,LCD_5x8DOTS);
   
    
  
   
    //LCDnoCursor();
    TRISAbits.TRISA3 = 0 ;
   // LCDnoBlink();
   // LCDsetBacklight(1);
     
    // memory_one_Write(EEPROM1,0x0000,0xAA);
    
    while (1)
    {
         
      // LCDsetCursor(0,0);
        //lcd_str("Meteo PIC 24 ");
     //  BME280_goForceMode();
        __delay_ms(200);
     //   input = BME280_readTemperature();
        //LCDsetCursor(0,1);
         //lcd_str("Temperature : ");
    //    ConvertFloattoLCDString(input);
    //    input = BME280_readHumidity();
        //LCDsetCursor(0,2);
         //lcd_str("Humidite : ");
   //     ConvertFloattoLCDString(input);
        //lcd_str(" %");
   //     input = BME280_readPressure();
        //LCDsetCursor(0,3);
         //lcd_str("Pression:");
     //   ConvertFloattoLCDString(input);
         //lcd_str(" hpa"); 
                
        
         LATAbits.LATA3 = 1;
         __delay_ms(1000);
        
            
        
         LATAbits.LATA3 = 0;
        __delay_ms(1000);
         
    }

 
}
