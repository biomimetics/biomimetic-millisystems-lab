/*
 * Signatures for interrupt handlers
 *
 * Created on 2009-4-8 by AMH, fgb
 */

#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

void SetupInterrupts(void);

void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void);
void __attribute__((__interrupt__, no_auto_psv)) _AddressError(void);

#endif // __INTERRUPTS_H
