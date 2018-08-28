//pjeanne 12/07/2018 : set the bme280 library more generic 


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

#define BME280_ADDRESS_W      0xEC          // define the default I2C address
#define BME280_ADDRESS_R      0xED         // define the default I2C address


// Name of Registers used in the BME280

#define    BME280_DIG_T1_REG   0x88
#define    BME280_DIG_T2_REG   0x8A
#define    BME280_DIG_T3_REG   0x8C
#define    BME280_DIG_P1_REG   0x8E
#define    BME280_DIG_P2_REG   0x90
#define    BME280_DIG_P3_REG   0x92
#define    BME280_DIG_P4_REG   0x94
#define    BME280_DIG_P5_REG   0x96
#define    BME280_DIG_P6_REG   0x98
#define    BME280_DIG_P7_REG   0x9A
#define    BME280_DIG_P8_REG   0x9C
#define    BME280_DIG_P9_REG   0x9E
    
    
#define    BME280_DIG_H1_REG   0xA1
#define    BME280_DIG_H2_REG   0xE1
#define    BME280_DIG_H3_REG   0xE3
#define    BME280_DIG_H4_REG   0xE4
#define    BME280_DIG_H5_REG   0xE5
#define    BME280_DIG_H6_REG   0xE7
    
    
#define    BME280_REGISTER_CHIPID       0xD0
#define    BME280_REGISTER_VERSION      0xD1
#define    BME280_REGISTER_SOFTRESET    0xE0
#define    BME280_REGISTER_CAL26        0xE1
#define    BME280_REGISTER_CONTROLHUMID     0xF2
#define    BME280_REGISTER_CONTROL          0xF4
#define    BME280_REGISTER_CONFIG           0xF5
#define    BME280_REGISTER_PRESSUREDATA     0xF7
#define    BME280_REGISTER_TEMPDATA         0xFA
#define    BME280_REGISTER_HUMIDDATA        0xFD


// structure to hold the calibration data that is programmed into the sensor in the factory
// during manufacture

 struct BME280_Calibration_Data
{
 
    
        uint16_t dig_T1;
        int16_t  dig_T2;
        int16_t  dig_T3;
    
        uint16_t dig_P1;
        int16_t  dig_P2;
        int16_t  dig_P3;
        int16_t  dig_P4;
        int16_t  dig_P5;
        int16_t  dig_P6;
        int16_t  dig_P7;
        int16_t  dig_P8;
        int16_t  dig_P9;
    
        uint8_t  dig_H1;
        int16_t  dig_H2;
        uint8_t  dig_H3;
        int16_t  dig_H4;
        int16_t  dig_H5;
        int8_t   dig_H6;
    
}; 

//fonctions

//int8_t BME280_init(void);
inline uint8_t BME280_read8(uint8_t reg);
inline int8_t BME280_write8(uint8_t reg,uint8_t value);
inline uint16_t BME280_read16(uint8_t reg);
uint16_t BME280_read16_LE(uint8_t reg);
int16_t BME280_readS16(uint8_t reg);
inline uint32_t BME280_read24(uint8_t reg);
int16_t BME280_readS16_LE(uint8_t reg);
void readSensorCoefficients(void);
//void displayCoefficients(void);
void BME280_goForceMode(void);
float BME280_readTemperature(void);
float BME280_readHumidity(void);
float BME280_readPressure(void);


