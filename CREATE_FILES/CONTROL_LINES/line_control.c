#include <stdint.h>
#include "line_control.h"
#include "../BOARD_PINOUT/board_pinout.h"
#include "../GPIO/gpio.h"

/*============================================================================*/
/*
#define _74HC138_A_PORT                  B
#define _74HC138_A_BIT                   0
#define _74HC138_A_MASK                  (1 << _74HC138_A_BIT)
 */

void RowControl(uint8_t* currRow, uint8_t* PosBit)
{
    uint8_t row = *currRow;
    uint8_t col = *PosBit;
    switch(row)
    {
        case 0x00:
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_A_PORT, _74HC138_A_MASK);
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_B_PORT, _74HC138_B_MASK);
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_C_PORT, _74HC138_C_MASK);
            row++;
            *currRow = row;
            break;
        case 0x01:
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_A_PORT, _74HC138_A_MASK);
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_B_PORT, _74HC138_B_MASK);
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_C_PORT, _74HC138_C_MASK);
            row++;
            *currRow = row;
            break;
        case 0x02:
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_A_PORT, _74HC138_A_MASK);
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_B_PORT, _74HC138_B_MASK);
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_C_PORT, _74HC138_C_MASK);
            row++;
            *currRow = row;
            break;
        case 0x03:
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_A_PORT, _74HC138_A_MASK);
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_B_PORT, _74HC138_B_MASK);
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_C_PORT, _74HC138_C_MASK);
            row++;
            *currRow = row;
            break;
        case 0x04:
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_A_PORT, _74HC138_A_MASK);
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_B_PORT, _74HC138_B_MASK);
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_C_PORT, _74HC138_C_MASK);
            row++;
            *currRow = row;
            break;
        case 0x05:
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_A_PORT, _74HC138_A_MASK);
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_B_PORT, _74HC138_B_MASK);
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_C_PORT, _74HC138_C_MASK);
            row++;
            *currRow = row;
            break;
        case 0x06:
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_A_PORT, _74HC138_A_MASK);
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_B_PORT, _74HC138_B_MASK);
            DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_C_PORT, _74HC138_C_MASK);
            row++;
            *currRow = row;
            break;
        case 0x07:
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_A_PORT, _74HC138_A_MASK);
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_B_PORT, _74HC138_B_MASK);
            DIGITAL_PIN_WRITE(PIN_LOW, _74HC138_C_PORT, _74HC138_C_MASK);
            row = 0x00;
            
            
           
                
            *currRow = row;
            *PosBit = col;
            break;
        default:
            for(;;);
    }
   
}