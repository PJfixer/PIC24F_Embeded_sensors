
#define _XTAL_FREQ  32000000UL
#define FCY 16000000UL
#include <libpic30.h>
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

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00
/// These are Bit-Masks for the special signals and background light
#define PCF_RS  0x01
#define PCF_RW  0x02
#define PCF_EN  0x04
#define PCF_BACKLIGHT 0x08

// Definitions on how the PCF8574 is connected to the LCD
// These are Bit-Masks for the special signals and Background
#define RSMODE_CMD  0
#define RSMODE_DATA 1

#define LOW 0 
#define HIGH 1


void _write2Wire( unsigned char  halfByte,  unsigned char  mode,  unsigned char  enable);
void _sendNibble(unsigned char halfByte, unsigned char mode);
void _send(unsigned char value, unsigned char mode);
inline void _command(unsigned char value);
inline void write(unsigned char value);
void LCDbegin(unsigned char cols, unsigned char rows, unsigned char charsize);
void LCDclear();
void LCDhome();
void LCDcreateChar(unsigned char location, unsigned char charmap[]);
void LCDsetCursor(unsigned char col, unsigned char row); 
void LCDsetBacklight(unsigned char brightness);
void LCDnoAutoscroll(void);
void LCDautoscroll(void);
 void LCDnoDisplay();
 void LCDdisplay();
 void LCDnoBlink();
 void LCDblink();
 void LCDnoCursor();
 void LCDcursor();
 void LCDscrollDisplayLeft();
 void LCDscrollDisplayRight();
 void LCDleftToRight();
 void LCDrightToLeft(); 
 void lcd_str(const char * s);
 void lcd_SendDec(unsigned int data);
 
 
