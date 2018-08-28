


#include "PCA8574_lcd.h"

#include <stdbool.h>
unsigned char _displayfunction ;
 unsigned char _numlines ;
 unsigned char _backlight ;
 unsigned char _displaymode ;
 unsigned char _displaycontrol;

void LCDbegin(unsigned char cols, unsigned char lines, unsigned char dotsize) {
  // cols ignored !
  _numlines = lines;

  _displayfunction = 0;

  if (lines > 1) {
    _displayfunction |= LCD_2LINE;
  }

  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != 0) && (lines == 1)) {
    _displayfunction |= LCD_5x10DOTS;
  }

 

  // initializing th display
  _write2Wire(0x00, LOW, false);
  __delay_us(50000); 

  // put the LCD into 4 bit mode according to the hitachi HD44780 datasheet figure 26, pg 47
  _sendNibble(0x03, RSMODE_CMD);
  __delay_us(4500); 
  _sendNibble(0x03, RSMODE_CMD);
  __delay_us(4500); 
  _sendNibble(0x03, RSMODE_CMD);
  __delay_us(150);
  // finally, set to 4-bit interface
  _sendNibble(0x02, RSMODE_CMD);

  // finally, set # lines, font size, etc.
  _command(LCD_FUNCTIONSET | _displayfunction);  

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKON;  
  LCDdisplay();

  // clear it off
  LCDclear();

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  _command(LCD_ENTRYMODESET | _displaymode);
}

void LCDclear()
{
  _command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  __delay_us(2000);  // this command takes a long time!
}

void LCDhome()
{
  _command(LCD_RETURNHOME);  // set cursor position to zero
  __delay_us(2000);  // this command takes a long time!
}


/// Set the cursor to a new position. 
void LCDsetCursor(unsigned char col, unsigned char row)
{
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54   };
  if ( row >= _numlines ) {
    row = _numlines-1;    // we count rows starting w/0
  }

  _command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void LCDnoDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  _command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LCDdisplay() {
  _displaycontrol |= LCD_DISPLAYON;
  _command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LCDnoCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  _command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LCDcursor() {
  _displaycontrol |= LCD_CURSORON;
  _command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void LCDnoBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  _command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LCDblink() {
  _displaycontrol |= LCD_BLINKON;
  _command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LCDscrollDisplayLeft(void) {
  _command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void LCDscrollDisplayRight(void) {
  _command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LCDleftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  _command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void LCDrightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  _command(LCD_ENTRYMODESET | _displaymode);
}


void LCDautoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  _command(LCD_ENTRYMODESET | _displaymode);
}


void LCDnoAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  _command(LCD_ENTRYMODESET | _displaymode);
}


void LCDsetBacklight(unsigned char brightness) {
  _backlight = brightness;
  // send no data but set the background-pin right;
  _write2Wire(0x00, RSMODE_DATA, false);
} // setBackl


void LCDcreateChar(unsigned char location, unsigned char charmap[]) {
    unsigned char  i ;
  location &= 0x7; // we only have 8 locations 0-7
  _command(LCD_SETCGRAMADDR | (location << 3));
  for (i=0; i<8; i++) {
    write(charmap[i]);
  }
}


inline void write(unsigned char value) {
  _send(value, RSMODE_DATA);
 
}


inline void _command(unsigned char value) {
  _send(value, RSMODE_CMD);
} // _command()



void _send(unsigned char value, unsigned char mode) {
  // separate the 4 value-nibbles
  unsigned char valueLo = value    & 0x0F;
  unsigned char valueHi = value>>4 & 0x0F;

  _sendNibble(valueHi, mode);
  _sendNibble(valueLo, mode);
}



void _sendNibble(unsigned char halfByte, unsigned char mode) {
  _write2Wire(halfByte, mode, true);
  __delay_us(1);    // enable doit estre superieur a 450 ns
  _write2Wire(halfByte, mode, false);
  __delay_us(40);   // une commande necessite 37 us
} // _sendNib
  
void _write2Wire(unsigned char  halfByte, unsigned char  mode, unsigned char enable) {
  // map the given values to the hardware of the I2C schema
  unsigned char i2cData = halfByte << 4;
  if (mode > 0) i2cData |= PCF_RS;
  // PCF_RW is never used.
  if (enable > 0) i2cData |= PCF_EN;
  if (_backlight > 0) i2cData |= PCF_BACKLIGHT;

I2C_START();
I2C_SEND_1_BYTE(0x7E);
I2C_SEND_1_BYTE(i2cData);
I2C_STOP();
} 

void lcd_str(const char * s)
{
    while(*s)
            write(*s++);
}

void lcd_SendDec(unsigned int data) // 
{
    unsigned char temp;
    temp=data/1000;
    write(temp+'0');
    data=data-temp*1000;
    temp=data/100;
    write(temp+'0');
    data=data-temp*100;
    temp=data/10;
    write(temp+'0');
    data=data-temp*10;
    write(data+'0');
}