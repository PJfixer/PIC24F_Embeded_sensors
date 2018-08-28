#include "RotaryEnc.h"
#include "app.h"
#include <p24FJ128GA202.h>


//pjeanne 09/07/2018

void __attribute__((interrupt, auto_psv ))_INT1Interrupt(void)
{
    // Clear the interrupt status flag associated with this interrupt - very important
    IFS1bits.INT1IF = 0 ;

    // Temporarily disable this interrupt - so it doesn't trigger multiple times due to button debounce
    IEC1bits.INT1IE = 0 ;

    // Invert LED
    LATBbits.LATB9 = ~PORTBbits.RB9;
    // Delay to await for the button position to stabilised
    __delay_ms(20);

    // Clear the interrupt status flag associated with this interrupt - very important
    IFS1bits.INT1IF = 0 ;

    // Re-enable the interrupt
    IEC1bits.INT1IE = 1 ;
}


void SetupInteruptEncoder(void)
{
    //Set PPS
    RPINR0bits.INT1R = 11 ;
    // End set PPS
    INTCON2bits.INT1EP = 0; // interupt on positive edge 
    IFS1bits.INT1IF = 0 ; // reset the flag
    IEC1bits.INT1IE = 1 ; // enable interupt
}

void EnableInteruptEncoder(void)
{
     IEC1bits.INT1IE = 1 ; // enable interupt
}

void DisableInteruptEncoder(void)
{
     IEC1bits.INT1IE = 0 ; // disable interupt
}
