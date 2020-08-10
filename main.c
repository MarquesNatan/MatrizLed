/*
 * File:   main.c
 * Author: Natan
 *
 * Created on 18 de Junho de 2020, 17:13
 */


// PIC18F4520 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "CREATE_FILES/BOARD_PINOUT/board_pinout.h"
#include "CREATE_FILES/GPIO/gpio.h"
#include "CREATE_FILES/SPI/spi.h"
#include "CREATE_FILES/CONTROL_LINES/line_control.h"
#include "CREATE_FILES/INTERRUPT/interrupts.h"
#include "CREATE_FILES/TIMER/timer.h"
#include "CREATE_FILES/SCROLLING_TEXT/scrolling_text.h"

#define _XTAL_FREQ 10000000
#define linesMatrix             8
int8_t currRow = 0;
int8_t posBit  = 0x00;
uint16_t i = 0;
    //  0b00000000, 0b01111110, 0b01100000, 0b01100000, 
    // 0b01111100,   0b01100000, 0b01100000, 0b01111110
    // 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    // 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55

uint8_t matrix[linesMatrix][linesMatrix];
uint8_t dataTrans[8] =
{
    //0x0FF, 0x0FF, 0x0FF, 0x0FF, 0x0FF, 0x0FF, 0x0FF, 0xFF 
    // 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x07F, 0x0FF
    0b00000000, 0b01111110, 0b01100000, 0b01100000, 
    0b01111100,   0b01100000, 0b01100000, 0b01111110
    // 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

/*
 * [0]  [0]  [0]  [0]  [0]  [0]  [0]  [0]                                                           
 * [0]  [1]  [1]  [1]  [1]  [1]  [1]  [0]                                                           
 * [0]  [0]  [0]  [0]  [0]  [1]  [1]  [0]                                                           
 * [0]  [0]  [0]  [0]  [0]  [1]  [1]  [0]                                                           
 * [0]  [0]  [1]  [1]  [1]  [1]  [1]  [0]                                                           
 * [0]  [0]  [0]  [0]  [0]  [1]  [1]  [0]                                                           
 * [0]  [0]  [0]  [0]  [0]  [1]  [1]  [0]                                                           
 * [0]  [1]  [1]  [1]  [1]  [1]  [1]  [0]
 */

void configure_pins(void);    

/* Interrupts Services Routines*/

void __interrupt()  TC0INT(void)
{
    if(INTCONbits.TMR0IF == 0x01)
    {
        INTCONbits.GIE = 0x00;
        T0CONbits.TMR0ON = 0x00;
        
        RowControl(&currRow, &posBit);
        ScrollingDisplay(matrix, &currRow, &posBit);
        
        TMR0 = 0xF63C; //  0x3CB0 -> 20 ms 0x6D84 -> 15 ms 0x9E58 -> 10 ms 0xF63C -> 1 ms
        INTCONbits.T0IF = 0x00;
        INTCONbits.GIE = 0x01;
        T0CONbits.TMR0ON = 0x01;
    }
}



void main(void) {
    
    uint8_t OnOff = 0x00;
    
    /* Configuration internal oscillator*/
    OSCCONbits.IRCF0 = 0x00;
    OSCCONbits.IRCF1 = 0x01;
    OSCCONbits.IRCF2 = 0x01;
    
    OSCCONbits.SCS0 = 0x00;
    OSCCONbits.SCS1 = 0x00;
    
    /*Configurations of ports*/
    ADCON1 = 0xFF; // All pins with digital
    CMCON = 0x07; // define pins 0 1 2 3 with outputs
    
    INTCON = 0x00; // Remove external interrupts
    INTCON2 = 0x00; // Enable all internal pull ups resistors
    INTCON3 = 0x00; // Disable all external interrupts
    
    WriteMatrix(matrix, dataTrans);
    configure_pins();
    Timer_Init();
    Timer_OnOff(1);
    Interrupts_Configure();
    
    
    
    
    while(1)
    {
        
        
    }
    return;
}


void configure_pins(void)
{
    CONFIGURE_PIN_DIGITAL(OUTPUT_PIN, _74HC138_A_PORT, _74HC138_A_MASK);
    CONFIGURE_PIN_DIGITAL(OUTPUT_PIN, _74HC138_B_PORT, _74HC138_B_MASK);
    CONFIGURE_PIN_DIGITAL(OUTPUT_PIN, _74HC138_C_PORT, _74HC138_C_MASK);
    CONFIGURE_PIN_DIGITAL(OUTPUT_PIN, _74HC138_G1_PORT, _74HC138_G1_MASK);
    
    DIGITAL_PIN_WRITE(PIN_HIGH, _74HC138_G1_PORT, _74HC138_G1_MASK);
    
    CONFIGURE_PIN_DIGITAL(OUTPUT_PIN, PIN_DS_595_PORT, PIN_DS_595_MASK);
    CONFIGURE_PIN_DIGITAL(OUTPUT_PIN, PIN_SHCP_595_PORT, PIN_SHCP_595_MASK);
    CONFIGURE_PIN_DIGITAL(OUTPUT_PIN, PIN_STCP_595_PORT, PIN_STCP_595_MASK);
    CONFIGURE_PIN_DIGITAL(OUTPUT_PIN, PIN_MR_595_PORT, PIN_MR_595_MASK);
}