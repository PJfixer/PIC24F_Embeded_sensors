/* 
 * File:   uart.h
 * Author: pierre
 *
 * Created on 8 février 2018, 19:23
 */

void putch( char data);
void usart_init(void);
void SendUART1(unsigned int data);
void UART1_SendStr(const char * s);
void UART1_SendDec(unsigned int data);
void UART1_SendHex(unsigned int data);
unsigned char setHEX(unsigned char ch);
void printTable(uint8_t * table,uint8_t size);