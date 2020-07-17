#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#define _XTAL_FREQ                  10000000
#include "spi.h"
#include "../GPIO/gpio.h"
#include "../BOARD_PINOUT/board_pinout.h"
/*============================================================================*/


void SPI_Init(spi_config* spiConfig)
{
    if(spiConfig != NULL)
    {
        /* Defines directions of pins used in spi communication */
        // CONFIGURE_PIN_DIGITAL(type, port, mask)
        
        CONFIGURE_PIN_DIGITAL(OUTPUT_PIN, SPI_MOSI_PORT, SPI_MOSI_MASK);
        CONFIGURE_PIN_DIGITAL(INPUT_PIN, SPI_MISO_PORT, SPI_MISO_MASK);
        CONFIGURE_PIN_DIGITAL(OUTPUT_PIN, SPI_CLOCK_PORT, SPI_CLOCK_MASK);
        CONFIGURE_PIN_DIGITAL(OUTPUT_PIN, SPI_SS_PORT, SPI_SS_MASK);
        
        /*Disables serial port and configures these pins as I/O pins*/
        SSPCON1bits.SSPEN = 0x00;
        
        /*Configure mode of operarion*/
        switch(spiConfig->masterMode)
        {
            case MASTER_MODE:
            {
                switch(spiConfig->baudRate)
                {
                    case CLOCK_SPEED_4:
                    {
                        /* Master mode clock = FOSC/4 */
                        SSPCON1bits.SSPM2 = 0x00;
                        SSPCON1bits.SSPM2 = 0x00;
                        SSPCON1bits.SSPM1 = 0x00;
                        SSPCON1bits.SSPM0 = 0x00;
                        break;
                    }
                    case CLOCK_SPEED_16:
                    {
                        /* Master mode clock = FOSC/16 */
                        SSPCON1bits.SSPM2 = 0x00;
                        SSPCON1bits.SSPM2 = 0x00;
                        SSPCON1bits.SSPM1 = 0x00;
                        SSPCON1bits.SSPM0 = 0x01;
                        break;
                    }
                    case CLOCK_SPEED_64:
                    {
                        /* Msater mode clock = FOSC/64 */
                        SSPCON1bits.SSPM2 = 0x00;
                        SSPCON1bits.SSPM2 = 0x00;
                        SSPCON1bits.SSPM1 = 0x01;
                        SSPCON1bits.SSPM0 = 0x00;
                        break;
                    }
                    case CLOCK_SPEED_TMR2:
                    {
                        /* Master mode clock = TMR2 output/2 */
                        SSPCON1bits.SSPM2 = 0x00;
                        SSPCON1bits.SSPM2 = 0x00;
                        SSPCON1bits.SSPM1 = 0x01;
                        SSPCON1bits.SSPM0 = 0x01;
                        break;
                    }  
                }
                break;
            }
            
            case SLAVE_MODE:
            {
                switch(spiConfig->controlSSPin)
                {
                    case SS_PIN_HARDWARE:
                    {
                         /*  SPI Slave mode, clock = SCK pin, SS pin control enabled*/
                        SSPCON1bits.SSPM2 = 0x00;
                        SSPCON1bits.SSPM2 = 0x01;
                        SSPCON1bits.SSPM1 = 0x00;
                        SSPCON1bits.SSPM0 = 0x00;
                        break;
                    }
                    case SS_PIN_SOFTWARE:
                    {
                         /*  SPI Slave mode, clock = SCK pin, SS pin control disabled
                             SS can be used as I/O pin */
                        SSPCON1bits.SSPM2 = 0x00;
                        SSPCON1bits.SSPM2 = 0x01;
                        SSPCON1bits.SSPM1 = 0x00;
                        SSPCON1bits.SSPM0 = 0x01; 
                        break;
                    }
                    
                }
                break;
            }
            default:
            {
                for(;;);
            }
        }
        
        switch(spiConfig->clockMode)
        {
            
            /* CPK -> Iddle state low level; active state high level 
                 * CKE -> Serial output data changes on transistion fron   active clock state 
                 *        to idle clock state
                 * SMP -> Data is sampled at middle of data output time
                 */
            case CLOCK_MODE_0:
            {
                SSPCON1bits.CKP = 0x00;
                SSPSTATbits.CKE = 0x01;
                SSPSTATbits.SMP = 0x00;
                break;
            }
            /*CLOCK MODE  1:
                 *  CKP -> Idle state for clock is a low level; active state is a high level
                 *  CKE -> Serial output data changes on transition from idle clock state 
                 *         to active clock state (see CKP bit)
                 *  SMP -> = Input data sampled at end of data output time
                 */
            case CLOCK_MODE_1:
            {
                SSPCON1bits.CKP = 0x00;
                SSPSTATbits.CKE = 0x00;
                SSPSTATbits.SMP = 0x01;
                
                break;
            }
            
            /*CLOCK MODE 2:
                 *  CKP ->  Idle state for clock is a high level; active state is a low level
                 *  CKE ->  Serial output data changes on transition from active clock state
                 *           to idle clock state (see CKP bit)
                 *  SMP ->  Input data sampled at middle of data output time
                 */
            case CLOCK_MODE_2:
            {
                SSPCON1bits.CKP = 0x01;
                SSPSTATbits.CKE = 0x01;
                SSPSTATbits.SMP = 0x00;
                break;
                
            }
            /*  CLOCK MODE 3:
                 *  CKP ->  Idle state for clock is a high level; active state is a low level
                 *  CKE ->  Serial output data changes on transition from idle clock state 
                 *          to active clock state (see CKP bit)
                 *  SMP -> Input data sampled at end of data output time
                 */
            case CLOCK_MODE_3:
            {
                SSPCON1bits.CKP = 0x01;
                SSPSTATbits.CKE = 0x00;
                SSPSTATbits.SMP = 0x01;
                break;
            }   
        }
    }
    else
    {
        for(;;);
    }
}

void SPI_OnOff(uint8_t OnOff)
{
    SSPCON1bits.SSPEN = OnOff;
}


void SPI_Write(uint8_t* transBuffer,  uint8_t currCol)
{
   // uint8_t i;
    uint8_t receive;
    
    /* Configure chip select as low (active)*/
    DIGITAL_PIN_WRITE(PIN_LOW, SPI_SS_PORT, SPI_SS_MASK);
   //  receive = SSPBUF; // -> Clear the buffer
    SSPBUF = transBuffer[currCol];
   //  while(!SSPSTATbits.BF);
    DIGITAL_PIN_WRITE(PIN_HIGH, SPI_SS_PORT, SPI_SS_MASK);
}


