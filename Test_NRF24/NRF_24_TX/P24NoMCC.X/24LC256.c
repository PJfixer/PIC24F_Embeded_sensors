/*pjeanne 13/07/2018  generic library for I2C EEPROM 24LC256 & 24LC128 */

#include "24LC256.h"


int8_t memory_one_Write(uint8_t memaddr,uint16_t regaddr,uint8_t data)
{
	I2C_START();
	if(I2C_SEND_1_BYTE(memaddr<<1) == 0) /* if valid write address continue operation */
	{
		if(I2C_SEND_1_BYTE((uint8_t)(regaddr>>8)) == 0) /* send high byte */
		{
			if(I2C_SEND_1_BYTE((uint8_t)regaddr) == 0) /* send low byte */
			{
				I2C_SEND_1_BYTE(data);/* send data byte */
				I2C_STOP();
				return 0;
			}
			else
			{
				I2C_STOP();
				return -1 ; 
			}
		}
		else
		{
			I2C_STOP();
			return -1 ; 
		}
		
	}
	else
	{
		I2C_STOP();
		return -1 ; 
	}


}


int8_t memory_one_Read(uint8_t memaddr,uint16_t regaddr,uint8_t * data)
{
	I2C_START();
	if(I2C_SEND_1_BYTE(memaddr<<1) == 0) /* if valid write address continue operation */
	{
		if(I2C_SEND_1_BYTE((uint8_t)(regaddr>>8)) == 0) /* send high byte */
		{
			if(I2C_SEND_1_BYTE((uint8_t)regaddr) == 0) /* send low byte */
			{
				I2C_START();
				if(I2C_SEND_1_BYTE((memaddr<<8)|0x01) == 0)  /* if valid read address continue operation */ 
				{
					*data = I2C_RECV_1_BYTE(0); /* get the data and send NACK*/
					I2C_STOP();
					return 0;
				}
				else
				{
					I2C_STOP();
					return -1 ; 
				}
			}
			else
			{
				I2C_STOP();
				return -1 ; 
			}
		}
		else
		{
			I2C_STOP();
			return -1 ; 
		}
		
	}
	else
	{
		I2C_STOP();
		return -1 ; 
	}
}
