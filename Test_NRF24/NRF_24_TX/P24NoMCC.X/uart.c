
#include <p24FJ128GA202.h>
#include "uart.h"
#include <stddef.h>
void usart_init(void)
{
    //TRIS
    TRISBbits.TRISB7 = 1 ;
    TRISBbits.TRISB6 = 0 ;
    //PPS
    
    RPINR18bits.U1RXR = 7; //RP7 = U1RX
    RPOR3bits.RP6R = 3; // RP6 = U1TX
    //CONFIG UART
    U1MODE = 0xA810;
    U1STA = 0x3400;
    U1BRG=103; 
    
    
  
    
   
}

void putch(  char data)
{
    if(U1STAbits.TRMT == 1)
    {
        U1TXREG = data ;
    }
}


    
void SendUART1(unsigned int data)
{
    while (U1STAbits.TRMT==0);
    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
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
            
            default: 
                return 'R';
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