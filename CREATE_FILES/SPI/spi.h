#ifndef SPI_H
#define SPI_H

#if (_BOARD == PIC18F4520)
#include <stdint.h>

/*============================================================================*/
#define CLOCK_MODE_0                    0
#define CLOCK_MODE_1                    1
#define CLOCK_MODE_2                    2
#define CLOCK_MODE_3                    3

#define SLAVE_MODE                      0
#define MASTER_MODE                     1


#define SS_PIN_HARDWARE                 0
#define SS_PIN_SOFTWARE                 1

#define CLOCK_SPEED_TMR2                0
#define CLOCK_SPEED_64                  1
#define CLOCK_SPEED_16                  2
#define CLOCK_SPEED_4                   3
/*==============================================================================*/

typedef struct
{
    uint8_t masterMode;
    uint8_t  clockMode;
    uint8_t controlSSPin;
    uint32_t baudRate;
    
}spi_config;


void SPI_Init(spi_config* spiConfig);
void SPI_OnOff(uint8_t OnOff);

void SPI_Write(uint8_t* transBuffer, uint8_t currCol);
// uint8_t SPI_Read(uint8_t* readByte, uint8_t length);

#elif



#endif






#endif /*SPI_H*/