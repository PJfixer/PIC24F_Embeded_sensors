
/**
 

  Company:
    Microchip Technology Inc.



*/


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


#define SPI1_DUMMY_DATA 0x0
#define SPI1_FIFO_FILL_LIMIT 0x8

/**
  SPI1 Status Enumeration

  @Summary
    Defines the status enumeration for SPI1.

  @Description
    This defines the status enumeration for SPI1.
 */
/*typedef enum {
    SPI1_SHIFT_REGISTER_EMPTY  = 1 << 7,
    SPI1_RECEIVE_OVERFLOW = 1 << 6,
    SPI1_RECEIVE_FIFO_EMPTY = 1 << 5,
    SPI1_TRANSMIT_BUFFER_FULL = 1 << 1,
    SPI1_RECEIVE_BUFFER_FULL = 1 << 0
}SPI1_STATUS; */



void SPI1_Initialize (void);
void SPI1_Exchange( uint8_t *pTransmitData, uint8_t *pReceiveData );
uint8_t SPI1_Exchange8bit( uint8_t data );
//SPI1_STATUS SPI1_StatusGet(void);

    
/*******************************************************************************
 End of File
*/
