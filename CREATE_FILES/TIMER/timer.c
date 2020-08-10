#include <xc.h>
#include <stdint.h>

/*============================================================================*/

void Timer_Init(void)
{
    /* Timer 0 configured as Timer of 16 bits*/
    T0CONbits.T08BIT = 0x00;
    T0CONbits.T016BIT = 0x00;
    
    
    /* Source clock of internal oscillator*/
    T0CONbits.T0CS = 0x00;
    
    /* Incrente on low-to-high transition on*/
    T0CONbits.T0SE = 0x00;
    T0CONbits.PSA = 0x01;
    
    /* dont use prescaler */
    T0CONbits.T0PS0 = 0x01;
    T0CONbits.T0PS1 = 0x01;
    T0CONbits.T0PS2 = 0x01;
    
    T0CONbits.TMR0ON = 0x01;
    
    /*== TIMER 1 CONFIGURATION */
    T1CONbits.T1RUN = 0x01;
    
    // Prescaler 
    T1CONbits.T1CKPS0 = 0x00;
    T1CONbits.T1CKPS1 = 0x00;
    
    // Clock Source 
    T1CONbits.TMR1CS = 0x00;
    
}

