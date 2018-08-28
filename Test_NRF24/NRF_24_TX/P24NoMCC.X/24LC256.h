/*pjeanne 13/07/2018  generic library for I2C EEPROM 24LC256 & 24LC128 */


#include "I2CA.h"

/************************************************************/
/******************GENERIC FUNCTION**************************/
/*Put here your custom I2C function for easy use of lib in your project*/
#define I2C_START I2C_start //function to send start condition
#define I2C_STOP I2C_stop //function to send stop condition 
#define I2C_RESTART I2C_restart // function to send restart condition 
#define I2C_WAIT_IDLE I2C_idle // function to wait for idle bus 
#define I2C_SEND_1_BYTE I2C_send_byte // fonction to send one byte 
#define I2C_RECV_1_BYTE I2C_receive_byte // fonction to receive one byte then send ACK or NACK

/*****************END GENERIC FUNCTION*******************************/

/**********************DEFINE I2C MEMORIES************************/
#define EEPROM1 0x70
#define EEPROM2 0x71
/**********************END DEFINE I2C MEMORIES************************/

int8_t memory_one_Write(uint8_t memaddr,uint16_t regaddr,uint8_t data);

int8_t memory_one_Read(uint8_t memaddr,uint16_t regaddr,uint8_t * data);