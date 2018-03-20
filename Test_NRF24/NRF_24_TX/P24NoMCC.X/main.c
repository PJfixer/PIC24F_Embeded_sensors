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

int main(void)
{
 
    SYSTEM_Initialize();
//uint8_t tx_address1[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
//uint8_t rx_address1[5] = {0xD7,0xD5,0xD7,0xD7,0xD7};

uint8_t tx_address2[5] = {0xD7,0xD5,0xD7,0xD7,0xD7};
uint8_t rx_address2[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};


uint8_t data_receive[4];

 csnPin1 = 1;
 cePin1 = 0;
 csnPin2 = 1;
 cePin2 = 0;



#ifndef SOFT

#else
  UART1_SendStr("Reglage emmeteur  (RX): \r\n");
  nrf24_config(20,PAYLOAD_LEN,1);
   nrf24_tx_address(tx_address2,1);
   nrf24_rx_address(rx_address2,1);     
   
      
   
  UART1_SendStr("configuration emmeteur 1 (RX) \r\n");
  nrf24_displayConfiguration(1);
   UART1_SendStr("\r\n\r\n\r\n\r\n\r\n\r\n");


                                         

      
    
   
   
   
 
#endif

 
  
    
    
    while (1)
    {
      
   
      
         LATBbits.LATB5 = 1;
         __delay_ms(1000);
         
          if(nrf24_dataReady(1))
          {
          
            nrf24_getData(data_receive,1);    
            UART1_SendHex(data_receive[0]);
            UART1_SendHex(data_receive[1]);
            UART1_SendHex(data_receive[2]);
            UART1_SendHex(data_receive[3]);
            UART1_SendStr("\r \n");
            clearTable(data_receive,4);
          }
            
            
         
         LATBbits.LATB5 = 0;
        __delay_ms(1000);
    }

 
}
