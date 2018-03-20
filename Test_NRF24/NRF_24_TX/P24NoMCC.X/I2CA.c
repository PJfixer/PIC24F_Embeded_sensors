
/*****************************************************************************
 *
 * I2C module Library routines
 *
 *****************************************************************************
 * FileName:        I2C.c
 * Processor:       PIC24
 * Compiler:        C30
 *
 * Author:          Frank Maier
 * Date:			21.04.2012
 *
 *****************************************************************************/


#include "I2CA.h"

/*****************************************************************************
 * Function: 	I2C_init
 * Overview: 	function initiates I2C1 module to baud rate BRG
 * Input: 		None
 * Output: 		None.
 *****************************************************************************/
void I2C_init(void)
{
	int temp;
	
	//TRISDbits.TRISD9 = 1;	// SCL Digital Input
	//TRISDbits.TRISD10 = 1; // SDA Digital Input

	//Baudrate
	I2C1BRG = I2C_BRATE;
	
	I2C1CONLbits.I2CEN = 0;	// Disable I2C Mode
	I2C1CONLbits.DISSLW = 1;	// Disable slew rate control
	IFS1bits.MI2C1IF = 0;	 // Clear Interrupt
	
	I2C1CONLbits.I2CEN = 1;	// Enable I2C Mode
	temp = I2C1RCV;	 // read buffer to clear buffer full

	I2C_stop();	 // set bus to idle
}


/*****************************************************************************
 * Function: 	I2C_idle
 * Overview: 	Waits until I2C Bud is inactive
 * Input: 		None
 * Output: 		None.
 *****************************************************************************/
void I2C_idle(void)
{
    // Wait until I2C Bus is Inactive
    while(I2C1CONLbits.SEN || I2C1CONLbits.RSEN || I2C1CONLbits.PEN || I2C1CONLbits.RCEN ||
          I2C1CONLbits.ACKEN || I2C1STATbits.TRSTAT);  
}


/*****************************************************************************
 * Function: 	I2C_start
 * Overview: 	function initiates a start condition on bus
 * Input: 		None
 * Output: 		None.
 *****************************************************************************/
void I2C_start(void)
{
	I2C1CONLbits.SEN = 1;	//Initiate Start condition
	I2C_idle();
}


/*****************************************************************************
 * Function: 	I2C_restart
 * Overview: 	function initiates a Repeated Start condition on bus
 * Input: 		None
 * Output: 		None.
 *****************************************************************************/
void I2C_restart(void)
{
	I2C1CONLbits.RSEN = 1;	//Initiate Repeated Start condition
	I2C_idle();
}


/*****************************************************************************
 * Function: 	I2C_stop
 * Overview: 	Resets the I2C bus to Idle
 * Input: 		None
 * Output: 		None.
 *****************************************************************************/
void I2C_stop(void)
{
	//initiate stop bit
	I2C1CONLbits.PEN = 1;
	while (I2C1CONLbits.PEN)
	{
		Nop();
	}
	
	I2C1CONLbits.RCEN = 0;		// Receives sequence not in progress
	IFS1bits.MI2C1IF = 0; 	// Clear Interrupt
	I2C1STATbits.IWCOL = 0;	// No Write Collision Detect
	I2C1STATbits.BCL = 0;		// No Master Bus Collision Detect

	I2C_idle();
}


/*****************************************************************************
 * Function: 	I2C_send_byte
 * Overview: 	function sends data
 * Input: 		8-bit Data to send
 * Output: 		1 = NACK was detected last, 0 = ACK was detected last 
 *****************************************************************************/
int I2C_send_byte(int data)
{
	// wait until transmit buffer is empty
	while (I2C1STATbits.TBF);
	IFS1bits.MI2C1IF = 0; // Clear Interrupt

	I2C1TRN = data; 			// load the outgoing data byte

	// If write collision occurs,return -1
  if(I2C1STATbits.IWCOL) return -1;
	
	I2C_idle();
	
	//Acknowledge Status bit 
	//1 = NACK was detected last, 0 = ACK was detected last
   
	return(I2C1STATbits.ACKSTAT);
}


/*****************************************************************************
 * Function: 	I2C_receive_byte
 * Overview: 	function receives and returns data
 * Input: 		1 = ACK, 0 = NACK
 * Output: 		received 8-bit byte
 * ATTENTION:	can hang (while(!RBF)), for debugging purpose
 *****************************************************************************/
unsigned char I2C_receive_byte(char ack)
{
	unsigned char data = 0;
    
    
	//I2C_idle();

	//set I2C module to receive
	I2C1CONLbits.RCEN = 1;
	while(I2C1CONLbits.RCEN);
	
	//wait for response
	while (!I2C1STATbits.RBF)
	{
		Nop();
	}

	//Hardware set at attempt to transfer I2CxRSR to I2CxRCV (cleared by software).
	// 1 = A byte was received while the I2CxRCV register is still holding the previous byte
	//I2C1STATbits.I2COV = 0;

	data = I2C1RCV;
    
 

	//set ACK
//	if ( ack ) {					// if ack=1
//		I2C1CONbits.ACKDT = 0;		//   then transmit an Acknowledge
//	} else {
//		I2C1CONbits.ACKDT = 1;		//   otherwise transmit a Not Acknowledge
//	}
    
	I2C1CONLbits.ACKDT = ack;
	I2C1CONLbits.ACKEN = 1;
	while(I2C1CONLbits.ACKEN == 1);
   
	//return data
	return data;
}


/*****************************************************************************
 * Function: 	I2C_write
 * Overview: 	full write prototype
 * Input: 		Device address, register subaddress, value to write
 * Output: 		None
 *****************************************************************************/
void I2C_write(char addr, char subaddr, char value)
{
	I2C_start();
	I2C_send_byte(addr);
	I2C_send_byte(subaddr);
	I2C_send_byte(value);
	I2C_stop();
}


/*****************************************************************************
 * Function: 	I2C_write
 * Overview: 	full read prototype
 * Input: 		Device address, register subaddress
 * Output: 		8-Byte read
 *****************************************************************************/
unsigned char I2C_read(char addr, char subaddr)
{
	unsigned char temp;
	
	// send address	
	I2C_start();
	I2C_send_byte(addr);
	I2C_send_byte(subaddr);
	
	// receive config
	I2C_restart();
	I2C_send_byte(addr | 0x01);
	temp = I2C_receive_byte(I2C_NACK);
	
	I2C_stop();
	
  return temp;
}

 
/*****************************************************************************
 * Function: 	I2C_ping
 * Overview: 	functions pings device, useful to initially check if device works
 * Input: 		Device address
 * Output: 		returns 0 for successful, 1 not found
 *****************************************************************************/
char I2C_ping(int addr)
{
  unsigned char temp;

   I2C_start();

   temp = I2C_send_byte(addr);

   I2C_stop();

  return temp;
}
