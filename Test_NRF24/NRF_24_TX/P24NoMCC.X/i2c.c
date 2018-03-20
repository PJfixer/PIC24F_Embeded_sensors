#include "i2c.h"
#define verbose
void i2c1_driver_driver_open(void) {
   // TRISBbits.TRISB8 = 1;
    //TRISBbits.TRISB9 = 1; // inutile le driver I2C prends la main sur TRIS
    I2C1CONLbits.I2CEN = 0;

   
    I2C1STAT = 0x0;

    I2C1CONL = 0x1200;
    I2C1CONH = 0x0000;
   
    I2C1BRG = 76;


    I2C1CONLbits.I2CEN = 1;

}

signed int  I2C_PutByte(unsigned char Byte)
{
   
     
            I2C1TRN = Byte;     // Chargement registre d'émission
            while(!_MI2C1IF);   // Attente fin émission
           
            
            if (I2C1STATbits.ACKSTAT != 0)
                {
                I2C_Stop();
                return I2C_NO_ACK;
                }
             _MI2C1IF = 0;       // Raz Flag
            
       
    return I2C_OK;
}
//------------------------------------------------------------------------------
signed int  I2C_GetByte( unsigned char *pByte, unsigned int EtatACK)
{

        
            I2C1CONLbits.ACKDT = EtatACK;    // type d'ACK à générer
            
            I2C1CONLbits.RCEN = 1;           // Lancer lecture
            while(!_MI2C1IF);               // Attente fin réception
                        
            *pByte = I2C1RCV;               // Lecture octet
            while(!_MI2C1IF);               
            _MI2C1IF = 0;                   // Raz Flag
            
            I2C1CONLbits.ACKEN = 1;          // Lancement génération ACK/NACK
            while(!_MI2C1IF);               
            _MI2C1IF = 0;                   // Raz Flag
                        
     
    
    
}
//------------------------------------------------------------------------------
void I2C_Stop(void)
{
   
       
    I2C1CONLbits.PEN = 1;
    while(!_MI2C1IF);   // Attente fin génération Stop
    _MI2C1IF = 0;       // Raz Flag
        
        
        
       
}
//------------------------------------------------------------------------------
void I2C_ReStart(void)
{
   
    I2C1CONLbits.RSEN = 1;
    while(!_MI2C1IF);   // Attente fin génération restart
    _MI2C1IF = 0;       // Raz Flag      
       
    
}

void  I2C_Start(void)
{
   
       
    I2C1CONLbits.SEN = 1;
    while(!_MI2C1IF);   // Attente fin génération start
    _MI2C1IF = 0;       // Raz Flag
         
        
        
    
    }

signed char I2C_Write( unsigned char Adr,unsigned char *pByte,unsigned char NbBytes)
{
    signed char Res;
    unsigned char i;
    
    I2C_Start();
    
    // Emission adresse en écriture
    Res = I2C_PutByte(Adr);
    if (Res != I2C_OK)
    {
        I2C_Stop();
        #ifdef verbose
        UART1_SendStr("Adresse errone ou esclave busy \n");
        #endif
        return I2C_NO_ACK;
    }
    
    for (i=0;i<NbBytes;i++)
    {
        Res = I2C_PutByte( pByte[i]);
        if (Res != I2C_OK)
        {
            I2C_Stop();
            #ifdef verbose
            UART1_SendStr("erreur lors de la transimission de la donne ");
            UART1_SendDec(i);
            UART1_SendStr("\n");        
            #endif
            return I2C_NO_ACK;
        }
    }
    I2C_Stop();
    return I2C_OK;
}
//------------------------------------------------------------------------------
signed char	I2C_Read(unsigned char Adr,unsigned char *pByte,unsigned char NbBytes)
{
    signed char Res;
    unsigned char Index;
    
    I2C_Start();    
    
    Res = I2C_PutByte(Adr);
    if (Res != I2C_OK)
        {
        I2C_Stop();
        
        return I2C_NO_ACK;
    }

    Index = 0;
    while(Index < (NbBytes - 1))
        {
        Res = I2C_GetByte(&pByte[Index],ACK);
        Index++;
        if (Res != I2C_OK)
            {
            I2C_Stop();
            return Res;  // Réception ACK ?
            }
        }
    
    Res = I2C_GetByte(&pByte[Index],ACK);    // Dernier octet lu sans ACQ 
    if (Res != I2C_OK)
    {
        I2C_Stop();
        return Res;  // Réception ACK ?
    }

    I2C_Stop();
    
    return I2C_OK;
}


signed char I2C_WriteThenRead(unsigned char Adr,unsigned char *pByteWR,unsigned char NbBytes2WR,unsigned char *pByteRD,unsigned char NbBytes2RD)
{
signed char Res;    
unsigned char Index;

    I2C_Start();
    
    // Emission adresse en écriture
    Res = I2C_PutByte(((Adr<<1) & 0xFE));
    if (Res != I2C_OK)
        {
        I2C_Stop();
        #ifdef verbose
        UART1_SendStr("Adresse errone ou esclave busy \n");
        #endif
        return I2C_NO_ACK;
        }
    
    for (Index=0;Index<NbBytes2WR;Index++)
    {
        Res = I2C_PutByte(pByteWR[Index]);
        if (Res != I2C_OK)
            {
            I2C_Stop();
            #ifdef verbose
            UART1_SendStr("erreur lors de la transimission de la donne ");
            UART1_SendDec(Index);
            UART1_SendStr("\n");        
            #endif
            return I2C_NO_ACK;
            }
    }
    
    I2C_ReStart();    
    
    Res = I2C_PutByte(((Adr << 1) | 0x01));
    UART1_SendStr("step1 \n");
    if (Res != I2C_OK)
        {
        I2C_Stop();
        #ifdef verbose
        UART1_SendStr("Adresse errone ou esclave busy \n");
        #endif
        return I2C_NO_ACK;
        }

    Index = 0;
    while(Index < (NbBytes2RD - 1))
        {
        Res = I2C_GetByte(&pByteRD[Index],ACK);
        Index++;
        if (Res != I2C_OK)
            {
            I2C_Stop();
             #ifdef verbose
            UART1_SendStr("erreur lors de la recption de la donne ");
            UART1_SendDec(Index);
            UART1_SendStr("\n");        
            #endif
            return Res;  // Réception ACK ?
            }
        
        }
    
    Res = I2C_GetByte(&pByteRD[Index],NO_ACK);    // Dernier octet lu sans ACQ (cf doc))
    
    if (Res != I2C_OK)
        {
        I2C_Stop();
        return Res;  // Réception ACK ?
        }

    I2C_Stop();
     
    return I2C_OK;
}

/*
 

void i2c1_driver_start(void) {
    I2C1CONLbits.SEN = 1;
    while(I2C1CONLbits.SEN)
    {
        // on attend la fin du start
    }
}

void i2c1_driver_restart(void) {
    I2C1CONLbits.RSEN = 1;
    while(I2C1CONLbits.RSEN)
    {
        // on attend la fin du start
    }
}

 void i2c1_driver_stop(void) {
    I2C1CONLbits.PEN = 1;
     while(I2C1CONLbits.PEN)
    {
        // on attend la fin du start
    }
}

 bool i2c1_driver_isNACK(void) {
    return (I2C1STATbits.ACKSTAT);
}

 void i2c1_driver_startRX(void) {
    I2C1CONLbits.RCEN = 1;
}

 char i2c1_driver_getRXData(void) {
   /*  while(I2C1STATbits.RBF == 0)
     {
         
     
    return I2C1RCV;
}

 void i2c1_driver_TXData(uint8_t d) {
    I2C1TRN = d;
     while(I2C1STATbits.TRSTAT)
    {
        
    }
}

 void i2c1_driver_sendACK(void) {
    I2C1CONLbits.ACKDT = 0;
    I2C1CONLbits.ACKEN = 1; // Envoie  ACK
   /*while(I2C1CONLbits.ACKEN)
    {
        
    } 
}

void i2c1_driver_sendNACK(void) {
    I2C1CONLbits.ACKDT = 1;
    I2C1CONLbits.ACKEN = 1; // envoie NACK
    /* while(I2C1CONLbits.ACKEN)
    {
        
    } 
}

 void i2c1_driver_releaseClock(void) {
    I2C1CONLbits.SCLREL = 1;
}

*/