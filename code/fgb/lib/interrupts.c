/*
 * Interrupt service routines
 *
 * Created on 2009-4-2 by fgb, AMH
 */

#include "ports.h"
#include "utils.h"
#include "pwm.h"


void SetupInterrupts(void)
{
    ConfigINT0(RISING_EDGE_INT & EXT_INT_ENABLE & EXT_INT_PRI_7); // Battery Supervisor
}


/******************************************************************************
 * Interrupt handler for the battery supervisor. 
 */

void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void)
{
    _INT0IF = 0;    // Clear the interrupt flag

    unsigned int i;

    _RF0 = 0;

    //Stop any running motors
    SetDCMCPWM(2, 0, 0);
    SetDCMCPWM(3, 0, 0);    

    for (i=0; i<5; i++) {
        asm volatile("btg   PORTF, #1");
        delay_ms(500);
    };
}


/******************************************************************************
 * Interrupt handlers for useful traps
 *
 * Note: Adapted from Microchip's traps.c  
 */

void __attribute__((__interrupt__, no_auto_psv)) _AddressError(void)
{
        INTCON1bits.ADDRERR = 0;        //Clear the trap flags
        while(1) {
            LED_2 = ~LED_2;
            delay_ms(50);
        };
}
