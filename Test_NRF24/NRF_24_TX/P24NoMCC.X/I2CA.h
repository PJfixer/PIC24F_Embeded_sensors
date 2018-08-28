/* 
 * File:   I2CA.h
 * Author: pierre
 *
 * Created on 19 février 2018, 21:04
 */


#include <p24FJ128GA202.h>
#include <stdbool.h>

void I2C_init(void);
void I2C_idle(void);
void I2C_start(void);
void I2C_restart(void);
void I2C_stop(void);
int I2C_send_byte(int data);
unsigned char I2C_receive_byte(char ack);
void I2C_Ack();
void I2C_NoAck();
void I2C_write(char addr, char subaddr, char value);
unsigned char I2C_read(char addr, char subaddr);
char I2C_ping(int addr);

// timing and baud rate settings 
#define I2C_BRATE   78     

#define I2C_ACK 		0
#define I2C_NACK 		1

