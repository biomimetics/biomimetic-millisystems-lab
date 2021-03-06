/*
 * Copyright (c) 2010, Regents of the University of California
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the University of California, Berkeley nor the names
 *   of its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Default Initialization Routines
 *
 * by Fernando L. Garcia Bermudez & Stanley S. Baek
 *
 * v.beta
 *
 * Revisions:
 *  Fernando L. Garcia Bermudez     2010-6-21   Initial release
 *  Stanley S. Baek                 2010-6-25   Expanded to even more boards
 *
 */

#ifndef __INIT_DEFAULT_H
#define __INIT_DEFAULT_H


// Sets up the MCU to use external clock.
//
// Settings: 40MHz
void SetupClock(void);

// Waits until the MCU clock is running on the external clock.
//
// The MCU is configured for 2-speed startup through the configuration bits
// present at the top of init_default.c. What this means is that it'll start
// running on an internal RC clock and then switch when the external clock has
// stabilized and the PLL has locked on it.
void SwitchClocks(void);

// Sets up the digital I/O ports.
//
// This function depends on which board it is being compiled to run on, and
// thus has more extensive documentation in init_default.c. By default, ADC
// pins are set for use as digital I/O's.
void SetupPorts(void);


#endif // __INIT_DEFAULT_H
