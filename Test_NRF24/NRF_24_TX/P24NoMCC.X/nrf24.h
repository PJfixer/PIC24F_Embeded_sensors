
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#define _XTAL_FREQ  32000000UL
#define FCY 16000000UL
#include <libpic30.h>
#include "nRF24L01.h"

#define SOFT
#define nrf24_ADDR_LEN 5
#define nrf24_CONFIG ((1<<EN_CRC)|(0<<CRCO))

#define NRF24_TRANSMISSON_OK 0
#define NRF24_MESSAGE_LOST   1

#define PAYLOAD_LEN 4

#define csnPin1 LATBbits.LATB15
#define cePin1  LATBbits.LATB14
#define csnPin2 LATBbits.LATB13 
#define cePin2  LATBbits.LATB9

#define sckPin  LATBbits.LATB10
#define mosiPin LATBbits.LATB12
#define misoPin PORTBbits.RB11

void set_ce(uint8_t state,uint8_t radioNb);
void set_csn(uint8_t state,uint8_t bus);
void set_sck(uint8_t state);
void set_mosi(uint8_t state);
uint8_t get_miso();
uint8_t spi_transfer(uint8_t tx);
void nrf24_transferSync(uint8_t* dataout,uint8_t* datain,uint8_t len);
void nrf24_transmitSync(uint8_t* dataout,uint8_t len);
void nrf24_configRegister(uint8_t reg, uint8_t value,uint8_t bus);
void nrf24_readRegister(uint8_t reg, uint8_t* value, uint8_t len,uint8_t bus);
void nrf24_writeRegister(uint8_t reg, uint8_t* value, uint8_t len,uint8_t bus) ;
void nrf24_powerUpRx(uint8_t radioNb);
void nrf24_config(uint8_t channel, uint8_t pay_length,uint8_t radioNb);
void nrf24_displayConfiguration(uint8_t radioNb);
void clearTable(uint8_t* tab,uint8_t size);
void nrf24_rx_address(uint8_t * adr,uint8_t RadioNb) ;
void nrf24_tx_address(uint8_t* adr,uint8_t RadioNb);
uint8_t nrf24_dataReady(uint8_t RadioNb) ;
uint8_t nrf24_rxFifoEmpty(uint8_t RadioNb);
uint8_t nrf24_payloadLength(uint8_t RadioNb);
void nrf24_getData(uint8_t* dta,uint8_t RadioNb) ;
uint8_t nrf24_retransmissionCount(uint8_t RadioNb);
void nrf24_send(uint8_t* value,uint8_t RadioNb);
uint8_t nrf24_isSending(uint8_t RadioNb);
uint8_t nrf24_getStatus(uint8_t RadioNb);
uint8_t nrf24_lastMessageStatus(uint8_t RadioNb);
void nrf24_powerUpTx(uint8_t RadioNb);
void nrf24_powerDown(uint8_t RadioNb);

