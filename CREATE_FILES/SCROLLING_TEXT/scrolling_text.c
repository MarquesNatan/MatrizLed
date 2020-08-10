#include <stdint.h>
#include <xc.h>
#include "scrolling_text.h"
#include "../GPIO/gpio.h"
#include "../BOARD_PINOUT/board_pinout.h"

#define _XTAL_FREQ                  10000000
/*============================================================================*/
void WriteMatrix(uint8_t matrix[][8], uint8_t vectorBytes[8])
{
    uint8_t byte = 0;
    uint8_t line = 0;
    uint8_t col;
    uint8_t aux =  1;
    
    for(line = 0; line < 8; line++)
    {
        for(col = 0; col < 8; col++)
        {
            aux = (1 << col);
            if((vectorBytes[line] & aux) >= 0x01)
            {
                matrix[line][col] = 0x01;
            }else
            {
                matrix[line][col] = 0x00;
            }
        }
    }
    
}

/*============================================================================*/
void ResetShift(void)
{
     // Reset antes de enviar os outros bits
        DIGITAL_PIN_WRITE(PIN_LOW, PIN_MR_595_PORT, PIN_MR_595_MASK);
        DIGITAL_PIN_WRITE(PIN_HIGH, PIN_STCP_595_PORT, PIN_STCP_595_MASK);
        __delay_us(1);
        DIGITAL_PIN_WRITE(PIN_LOW, PIN_STCP_595_PORT, PIN_STCP_595_MASK);
        DIGITAL_PIN_WRITE(PIN_HIGH, PIN_MR_595_PORT, PIN_MR_595_MASK);
}

void ScrollingDisplay(uint8_t matrix[][8], int8_t* line, int8_t* posBit)
{
    DIGITAL_PIN_WRITE(PIN_LOW, PIN_MR_595_PORT, PIN_MR_595_MASK);
    DIGITAL_PIN_WRITE(PIN_HIGH, PIN_STCP_595_PORT, PIN_STCP_595_MASK);
    __delay_us(1);
    DIGITAL_PIN_WRITE(PIN_LOW, PIN_STCP_595_PORT, PIN_STCP_595_MASK);
    DIGITAL_PIN_WRITE(PIN_HIGH, PIN_MR_595_PORT, PIN_MR_595_MASK);
    
    /*================================================================*/
    
    if(*posBit != 0x07)
    {
        // Enviar do ultimo até o bit atual
        int8_t lastBit;
        for(lastBit = 7; lastBit >= *posBit; lastBit--)
        {
            if(matrix[*line][lastBit])
            {
                DIGITAL_PIN_WRITE(PIN_HIGH, PIN_DS_595_PORT, PIN_DS_595_MASK);
                DIGITAL_PIN_WRITE(PIN_HIGH, PIN_SHCP_595_PORT, PIN_SHCP_595_MASK);
                __delay_us(1);
                DIGITAL_PIN_WRITE(PIN_LOW, PIN_SHCP_595_PORT, PIN_SHCP_595_MASK);
            }
            else
            {
                DIGITAL_PIN_WRITE(PIN_LOW, PIN_DS_595_PORT, PIN_DS_595_MASK);
                DIGITAL_PIN_WRITE(PIN_HIGH, PIN_SHCP_595_PORT, PIN_SHCP_595_MASK);
                __delay_us(1);
                DIGITAL_PIN_WRITE(PIN_LOW, PIN_SHCP_595_PORT, PIN_SHCP_595_MASK);
            }
        }
        
    }
    else
    {
        if(matrix[*line][*posBit])
        {
            DIGITAL_PIN_WRITE(PIN_HIGH, PIN_DS_595_PORT, PIN_DS_595_MASK);   
            DIGITAL_PIN_WRITE(PIN_HIGH, PIN_SHCP_595_PORT, PIN_SHCP_595_MASK);
            __delay_us(1);
            DIGITAL_PIN_WRITE(PIN_LOW, PIN_SHCP_595_PORT, PIN_SHCP_595_MASK);
        }
        else
        {
            DIGITAL_PIN_WRITE(PIN_LOW, PIN_DS_595_PORT, PIN_DS_595_MASK);
            DIGITAL_PIN_WRITE(PIN_HIGH, PIN_SHCP_595_PORT, PIN_SHCP_595_MASK);
            __delay_us(1);
            DIGITAL_PIN_WRITE(PIN_LOW, PIN_SHCP_595_PORT, PIN_SHCP_595_MASK);
        }
    }
    
    DIGITAL_PIN_WRITE(PIN_HIGH, PIN_STCP_595_PORT, PIN_STCP_595_MASK);
    __delay_us(1);
    DIGITAL_PIN_WRITE(PIN_LOW, PIN_STCP_595_PORT, PIN_STCP_595_MASK);
    (*line < 0x07)?((*line)++):((*line) = 0x00);
}


