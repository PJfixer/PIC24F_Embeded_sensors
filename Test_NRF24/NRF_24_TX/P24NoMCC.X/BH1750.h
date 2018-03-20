

#define _XTAL_FREQ  32000000UL
#define FCY 16000000UL
#include <libpic30.h>
#include "I2CA.h"



unsigned char LireLux(unsigned char resolution,unsigned char *data);
unsigned char BH1750_Write(unsigned char data);
unsigned char BH1750_Read(unsigned char *data);


//BH1750 command 
#define	BH1750_address_w		0x46                               
#define	BH1750_address_r		0x47 

#define	power_down				0x00
#define power_up				0x01
#define reset					0x07 
#define cont_H_res_mode1  		0x10 
#define cont_H_res_mode2  		0x11  
#define cont_L_res_mode   		0x13                                          
#define one_time_H_res_mode1  	0x20 
#define one_time_H_res_mode2  	0x21
#define one_time_L_res_mode  	0x23    