/* 
 * File:   i2c.h
 * Author: pierre
 *
 * Created on February 8, 2018, 1:31 PM
 */
#include <p24FJ128GA202.h>
#include <stdbool.h>
/*void i2c1_driver_driver_open(void);
void i2c1_driver_start(void);
void i2c1_driver_restart(void) ;
void i2c1_driver_stop(void);
bool i2c1_driver_isNACK(void);
void i2c1_driver_startRX(void);
char i2c1_driver_getRXData(void);
void i2c1_driver_TXData(uint8_t d);
void i2c1_driver_sendACK(void);
void i2c1_driver_sendNACK(void);
void i2c1_driver_releaseClock(void); */



#define	I2C_OK              0
#define	I2C_NO_ACK          -1
#define	I2C_BAD_ADDRESS     -2

#define	ACK                 0
#define	NO_ACK              1
signed char I2C_Write( unsigned char Adr,unsigned char *pByte,unsigned char NbBytes);
signed char	I2C_Read(unsigned char Adr,unsigned char *pByte,unsigned char NbBytes);
signed int  I2C_PutByte(unsigned char Byte);
signed int  I2C_GetByte( unsigned char *pByte, unsigned int EtatACK);
signed char I2C_WriteThenRead(unsigned char Adr,unsigned char *pByteWR,unsigned char NbBytes2WR,unsigned char *pByteRD,unsigned char NbBytes2RD);
void I2C_Stop(void);
void I2C_ReStart(void);
void  I2C_Start(void);
