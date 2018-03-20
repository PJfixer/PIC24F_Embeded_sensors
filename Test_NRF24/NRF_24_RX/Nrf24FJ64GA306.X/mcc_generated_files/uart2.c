/**
  UART2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    uart2.c

  @Summary
    This is the generated driver implementation file for the UART2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for UART2.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.45
        Device            :  PIC24FJ64GA306
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.32
        MPLAB             :  MPLAB X 3.61
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "uart2.h"

/**
  Section: UART2 APIs
*/

void UART2_Initialize(void)
{
/**    
     Set the UART2 module to the options selected in the user interface.
     Make sure to set LAT bit corresponding to TxPin as high before UART initialization
*/
    // STSEL 1; IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; RXINV disabled; UEN TX_RX; 
    U2MODE = (0x8008 & ~(1<<15));  // disabling UARTEN bit   
    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; OERR NO_ERROR_cleared; URXISEL RX_ONE_CHAR; UTXBRK COMPLETED; UTXEN disabled; ADDEN disabled; 
    U2STA = 0x0000;
    // BaudRate = 9600; Frequency = 10000000 Hz; BRG 259; 
    U2BRG = 0x0103;
    
    U2MODEbits.UARTEN = 1;  // enabling UARTEN bit
    U2STAbits.UTXEN = 1; 
   
}


uint8_t UART2_Read(void)
{
    while(!(U2STAbits.URXDA == 1))
    {
        
    }

    if ((U2STAbits.OERR == 1))
    {
        U2STAbits.OERR = 0;
    }

    

    return U2RXREG;
}

void UART2_Write(uint8_t txData)
{
    while(U2STAbits.UTXBF == 1)
    {
        
    }

    U2TXREG = txData;    // Write the data byte to the USART.
}

UART2_STATUS UART2_StatusGet (void)
{
    return U2STA;
}

int __attribute__((__section__(".libc.write"))) write(int handle, void *buffer, unsigned int len) {
    int i;
    while(U2STAbits.TRMT == 0);  
    for (i = len; i; --i)
    {
        while(U2STAbits.TRMT == 0);
        U2TXREG = *(char*)buffer++;        
    }
    return(len);
}

/**
  End of File
*/


    
void SendUART1(unsigned int data)
{
    while (U2STAbits.TRMT==0);
    if(U2MODEbits.PDSEL == 3)
        U2TXREG = data;
    else
        U2TXREG = data & 0xFF;
}

void UART1_SendStr(const char * s)
{
    while(*s)
            SendUART1(*s++);
}

void UART1_SendDec(unsigned int data) // 
{
    unsigned char temp;
    temp=data/1000;
    SendUART1(temp+'0');
    data=data-temp*1000;
    temp=data/100;
    SendUART1(temp+'0');
    data=data-temp*100;
    temp=data/10;
    SendUART1(temp+'0');
    data=data-temp*10;
    SendUART1(data+'0');
}

void UART1_SendHex(unsigned int data) // 
{
    unsigned char temp;
     SendUART1('0');
     SendUART1('x');
    temp = data>>4;
    SendUART1(setHEX(temp));
    temp = data&0x0F;
    SendUART1(setHEX(temp));
    
    
}

unsigned char setHEX(unsigned char ch)
{
    if(ch >= 0 && ch <= 9)
    {
        return (ch+'0');
    }
    else
    {
        switch(ch)
        {
            case 10:
                return 'A';
            break; 
            case 11:
                return 'B';
            break; 
            case 12:
                return 'C';
            break; 
            case 13:
                return 'D';
            break; 
            case 14:
                return 'E';
            break; 
            case 15:
                return 'F';
            break; 
        }
    }
}


void printTable(uint8_t * table,uint8_t size)
{
    uint8_t i ;
    for(i = 0; i<size;i++)
    {
        if (table[i] != NULL)
        {
            UART1_SendHex(table[i]);
            UART1_SendStr(" ");
        }
    }
}     