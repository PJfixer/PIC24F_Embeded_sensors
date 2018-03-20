#include "BH1750.h"

unsigned char BH1750_Write(unsigned char data1)
{
  	
	I2C_start();
	I2C_send_byte(BH1750_address_w);
	I2C_send_byte(data1);
  I2C_stop();
}

unsigned char BH1750_Read(unsigned char *data)
{
	
	I2C_start();
	I2C_send_byte(BH1750_address_r);
	data[0] =  I2C_receive_byte(I2C_ACK);
  data[1] =  I2C_receive_byte(I2C_NACK);
    I2C_idle();
    I2C_stop();
     
}



unsigned char LireLux(unsigned char resolution,unsigned char *data)
{
  
  BH1750_Write(power_up);
  switch(resolution)
  {
    case 0:  // 1 mesure haute precision 
      BH1750_Write(one_time_L_res_mode);
    break;
    case 1:  // 1 mesure haute precision 
      BH1750_Write(one_time_H_res_mode1);
    break;
    case 2:  // 1 mesure haute precision 
      BH1750_Write(one_time_H_res_mode2);
    break;
    default: // par defaut haute precison 
      BH1750_Write(one_time_H_res_mode1);
    break;
  }
  
  __delay_ms(200);
  BH1750_Read(data);
  
     
}
