/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.45
        Device            :  PIC24FJ64GA306
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.32
        MPLAB             :  MPLAB X 3.61
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"




/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    csnPin1 = 1 ; 
    cePin1 = 0 ;
    
uint8_t tx_address1[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8_t rx_address1[5] = {0xD7,0xD5,0xD7,0xD7,0xD7};
uint8_t data_array[4] = {0xAA,0xBB,0xCC,0x00} ;
uint8_t temp = 0 ; 
__delay_ms(2000);
nrf24_config(20,PAYLOAD_LEN,1);
nrf24_tx_address(tx_address1,1);
nrf24_rx_address(rx_address1,1); 

nrf24_displayConfiguration(1);
    
    
    while (1)
    {
        data_array[3]++;
        nrf24_send(data_array,1);        
        

        while(nrf24_isSending(1));

   
        temp = nrf24_lastMessageStatus(1);

        if(temp == NRF24_TRANSMISSON_OK)
        {                    
            printf("> Tranmission went OK\r\n");
        }
        else if(temp == NRF24_MESSAGE_LOST)
        {                    
            printf("> Message is lost ...\r\n");    
        }
        
        temp = nrf24_retransmissionCount(1);
		printf("> Retranmission count: %d \r\n",temp);
		printf("\r\n");  
        
        LATFbits.LATF0 =1 ;
        
      
        __delay_ms(1000);
        LATFbits.LATF0 = 0;
       
        __delay_ms(1000);
        
       
       
    }

    return -1;
}
/**
 End of File
*/