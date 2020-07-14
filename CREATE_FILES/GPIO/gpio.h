#ifndef GPIO_H 
#define GPIO_H 
#define _BOARD          PIC18F4520
/*============================================================================*/
#if (_BOARD == PIC18F4520)
    #include <xc.h>
    #include <pic18f4520.h>
/*============================================================================*/
#define PIN_LOW                 0x00
#define PIN_HIGH                0x01

#define OUTPUT_PIN              0x00
#define INPUT_PIN               0x01

/*============================================================================*/
#define PASTE2B(a, b)           a##b
#define PASTE2(a, b)            PASTE2B(a, b)

#define PASTE3B(a, b, c)        a##b##c
#define PASTE3(a, b, c)         PASTE3(a, b, c)
/*============================================================================*/

/*Configure pin digital
 * TRIS##PORT##bits.##TRIS##BIT = 0x00;
 */

        #define CONFIGURE_PIN_DIGITAL(type, port, mask)                        \
                    if(OUTPUT_PIN ==  type)                                    \
                        PASTE2(TRIS, port) = (PASTE2(TRIS, port) & (~mask));   \
                    if(INPUT_PIN == type)                                      \
                        PASTE2(TRIS, port) = (PASTE2(TRIS, port) | mask);
/*============================================================================*/
        #define DIGITAL_PIN_WRITE(value, port, mask)                           \
                    if(PIN_LOW == value)                                       \
                        PASTE2(LAT, port) =  (PASTE2(PORT, port) & ~(mask));   \
                    if(PIN_HIGH == value)                                      \
                        PASTE2(LAT, port) = (PASTE2(PORT, port) | mask);
/*============================================================================*/
        #define DIGITAL_PIN_READ(port, bit)                                    \
                ((PASTE2(PORT, port) >> bit)& 0b00000001)
/*============================================================================*/
        #define DIGITAL_PIN_TOGGLE(port, mask)                                 \
                   PASTE2(LAT, port) = (PASTE2(PORT, port) ^ mask);
/*============================================================================*/


/*============================================================================*/

#elif
    #erro: Board not defined
#endif








#endif /*GPIO_H*/