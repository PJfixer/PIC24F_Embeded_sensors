#include "app.h"



void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    usart_init();
    I2C_init();
  //  SPI1_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // CF no clock failure; NOSC FRCPLL; SOSCEN disabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONL((uint8_t) (0x0100 & 0x00FF));
    // PLLEN disabled; RCDIV FRC/1; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3000;
    // STOR disabled; STORPOL Interrupt when STOR is 1; STSIDL disabled; STLPOL Interrupt when STLOCK is 1; STLOCK disabled; STSRC SOSC; STEN disabled; TUN Center frequency; 
    OSCTUN = 0x0000;
    // ROEN disabled; ROSEL FOSC; ROSIDL disabled; ROSWEN disabled; ROOUT disabled; ROSLP disabled; 
    REFOCONL = 0x0000;
    // RODIV 0; 
    REFOCONH = 0x0000;
    // ROTRIM 0; 
    REFOTRIML = 0x0000;
}

void PIN_MANAGER_Initialize(void)
{
    /****************************************************************************
     * toute les sorties a zero
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;

    /****************************************************************************
     * reglage entrée sortie 
     ***************************************************************************/
    TRISA = 0x000F;
    TRISB = 0xFFEF;
    TRISBbits.TRISB5 = 0;
    

    /****************************************************************************
     * reglage Weak Pull Up etWeak Pull Down SFR(s)
     ***************************************************************************/
    CNPD1 = 0x0000;
    CNPD2 = 0x0000;
    CNPD3 = 0x0000;
    CNPU1 = 0x0000;
    CNPU2 = 0x0000;
    CNPU3 = 0x0000;

    /****************************************************************************
     * reglage  Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;

    /****************************************************************************
     * reglage canaux analogique Configuration SFR(s)
     ***************************************************************************/
    ANSA = 0x000F;
    ANSB = 0x0000;
    TRISBbits.TRISB9 = 0 ; // CE for Nrf24L01 N°2
    TRISBbits.TRISB15 = 0;   // CS N°2
    TRISBbits.TRISB14 = 0; //  CE for Nrf24l01 N°1
    TRISBbits.TRISB10 = 0;  // SCK OUT
    TRISBbits.TRISB13 = 0; //  CS N°1 
    TRISBbits.TRISB12 = 0;  // SDO
    TRISBbits.TRISB11 = 1;  // SDI
   /* RPOR5bits.RP10R = 0x0008;   //RB10->SPI1:SCK1OUT;
    RPOR6bits.RP13R = 0x0009;   //RB13->SPI1:SS1OUT;
    RPINR20bits.SDI1R = 0x000B;   //RB11->SPI1:SDI1;
    RPOR6bits.RP12R = 0x0007;   //RB12->SPI1:SDO1; */

}




