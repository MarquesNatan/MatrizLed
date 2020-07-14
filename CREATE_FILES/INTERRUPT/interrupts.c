#include <xc.h>
/*============================================================================*/

void Interrupts_Configure(void)
{
    // Bits of configurations interrupts
    
    /* Enable global interrupts and enable high priority interrupts */
    INTCONbits.GIE = 0x01; 
    INTCONbits.GIEH = 0x01;     
    
    /* Enable interrupts level */
    RCONbits.IPEN = 0x01;
    
    /* Enable peripheral interrupts and low priority interrupts*/
    INTCONbits.PEIE = 0x01;
    INTCONbits.GIEL = 0x01;
    
    
    /*Cofigurations of interrutions to timer 0 module*/
    /* Enable interruptions to timer 0 module
     * Set high priority to interrution of timer 0 module
     * 
     */
    INTCONbits.TMR0IE = 0x01;
    INTCON2bits.TMR0IP = 0x01;
}

/*============================================================================*/