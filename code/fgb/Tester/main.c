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
 * Testing Platform
 *
 * by Fernando L. Garcia Bermudez
 *
 * v.beta
 *
 * Revisions:
 *  Fernando L. Garcia Bermudez     2010-2-25    Initial release
 *
 */


// Define the test you'd like to perform:
#define __TEST_GYRO
// Possible tests are:
// __TEST_CLOCK
// __TEST_DELAY
// __TEST_SUPERVISOR
// __TEST_UART
// __TEST_OVCAM
// __TEST_PWM
// __TEST_ADC
// __TEST_DMA_TRIG_ADC
// __TEST_ADC_VIA_DMA
// __TEST_DFMEM
// __TEST_OVCAM_VIA_DFMEM
// __TEST_DFMEM_VIA_DMA
// __TEST_STOPWATCH
// __TEST_ACCEL
// __TEST_GYRO


// Tests the clock setup procedure.
//
// This should light up the power LED once the initialization routines finish
// executing.
#if defined(__TEST_CLOCK)

#include "init_default.h"
#include "utils.h"

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();  
    SwitchClocks();
    LED_1 = 1;

    /* Program */
    while(1){}

    return 0;
}


// Tests the delay subroutine.
//
// This should toggle the error LED every half second.
#elif defined(__TEST_DELAY)

#include "init_default.h"
#include "utils.h"

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();    
    SwitchClocks();  
    LED_1 = 1;

    /* Program */
    while(1){

        // Loop for testing precise timing w/scope
        //asm volatile("LOOPIT: btg   LATB, #12 ");
        //delay_us(100);
	    //asm volatile("goto LOOPIT");
        
        LED_2 = ~LED_2;
        delay_ms(500);
    
    }

    return 0;
}


// Tests the battery supervisor interrupt.
//
// This should toggle 5 times the error LED (every .5s) once the voltage to the
// board falls below the supervisor threshold.
#elif defined(__TEST_SUPERVISOR)

#include "init_default.h"
#include "utils.h"

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupInterrupts();    
    SwitchClocks();
    LED_1 = 1;

    /* Program */
    while(1){}

    return 0;
}


// Tests the UART port.
//
// This should send back whatever it receives, blocking the flow until it
// receives a byte or sends it back.
//
// Interface: testUART.py
#elif defined(__TEST_UART)

#include "init_default.h"
#include "utils.h"

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupUART();   
    SwitchClocks();
    LED_1 = 1;

    /* Program */
    while(1){
    
        // Wait for a new byte and send it back
        LED_1 = 1;
        while(!U2STAbits.URXDA);
        U2TXREG = U2RXREG;
        while(U2STAbits.UTXBF);
        LED_1 = 0;
    
    }

    return 0;
}


// Tests the OmniVision Camera.
//
// This should send back the first 100 lines of a QQVGA picture.
//
// Interface: testOVCAM.py
#elif defined(__TEST_OVCAM)

#include "init.h"
#include "init_default.h"
#include "utils.h"
#include "ovcam.h"
#include "uart.h"

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupUART();
    SwitchClocks();
    ovcamSetup();
    LED_1 = 1;

    /* Declarations */
    unsigned int i, j, imcols=160, imrows=100, rowcnt;
    unsigned char image[imrows][imcols];
    
    /* Program */
    while(1){
        
        // Wait for a register and send back its contents
        while(!U2STAbits.URXDA);
        WriteUART2(ovcamReadRegister(ReadUART2()));

        // Get the size of image to be captured/sent and confirm
        while(!U2STAbits.URXDA);
        if (ReadUART2() == 1)
        {
            // Get requested image resolution
            while(!U2STAbits.URXDA);
            imcols = ReadUART2();
            while(!U2STAbits.URXDA);
            imrows = ReadUART2();

            // Confirm image resolution
            WriteUART2(imcols);
            WriteUART2(imrows);
   
            // Throw out frame fraction
            ovcamWaitForNewFrame();

            // Send rows to RAM
            for (rowcnt = 0; rowcnt < imrows; rowcnt++)
            {
                ovcamGetRow(image[rowcnt]);
            }
            //ovcamGetFrame(image);

            // Send the captured image off-board
            for (i = 0; i < imrows; i++) {
                for (j = 0; j < imcols; j++) {
                    WriteUART2(image[i][j]);
                    while(U2STAbits.UTXBF);
                }
            }
        }
    }

    return 0;
}


// Tests the PWM output.
//
// This should turn on the PWM output, incresing the duty cycle every .5s until
// starting again.
#elif defined(__TEST_PWM)

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupPWM();   
    SwitchClocks();
    LED_1 = 1;

    /* Declarations */
    unsigned int i, j;   

    /* Program */
    while(1){
    
        // Run a staircase of 0, 25, 50, 75, 100 on the PWM with each step
        // taking .5s and then cycle
        for (i=0; i<=4; i++) {
            SetDCMCPWM(2, (unsigned int)(2.0 * i * 25/100.0 * PTPERvalue), 0);
            for (j=0; j<1000; j++) { delay_us(500); }   // Waste approx .5s
        }    
    }

    return 0;
}


// Tests the ADC.
//
// This should get bEMF measurements from the PWM driving a motor at changing
// speeds and send it off-board.
//
// Interface: testADC.py
#elif defined(__TEST_ADC)

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupUART();
    SetupPWM();
    SetupADC();
    SwitchClocks();
    LED_1 = 1;    

    /* Declarations */
    unsigned int i, j, Vm;   

    /* Program */
    while(1){
    
        // Wait until a 1 arrives
        while(!DataRdyUART2());
        if (ReadUART2() == 1) {

            _ADON = 1;

            // Run a staircase of 0, 25, 50, 75, 100 on the PWM with each step
            // taking .5s and then cycle
            for (i=0; i<=4; i++) {
                SetDCMCPWM(2, (unsigned int)(2.0 * i * 25/100.0 * PTPERvalue), 0);
                for (j=0; j<1000; j++) { delay_us(500); }   // Waste approx .5s

                // Get bEMF and send it offboard
                Vm = ADC1BUF0;
                while(U2STAbits.UTXBF);
                WriteUART2((unsigned char)(((Vm >> 5) & 0x001F) | 0x0080));
                while(U2STAbits.UTXBF);
                WriteUART2((unsigned char)(Vm & 0x001F));

            }

            // Finalize transmission
            while(U2STAbits.UTXBF);
            WriteUART2(0x0060);

        }
    }

    return 0;
}


// Tests DMA triggered by ADC.
//
// This script sends back the address the DMA is currently accessing in it's
// RAM space.
//
// Interface: testDMAwADC.py
#elif defined(__TEST_DMA_TRIG_ADC)

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupUART();
    SetupPWM();
    SetupDMA();
    SetupADC();
    SwitchClocks();
    LED_1 = 1;

    /* Declarations */
    unsigned int i, j, reg;   

    /* Program */
    while(1){

        // Wait until a 1 arrives
        while(!DataRdyUART2());
        if (ReadUART2() == 1) {

            _ADON = 1;

            // Send latest DMA address accessed
            reg = DSADR;
            while(U2STAbits.UTXBF);
            WriteUART2((unsigned char)(reg >> 8));
            while(U2STAbits.UTXBF);
            WriteUART2((unsigned char)(reg));

        }
    }

    return 0;
}


// Tests the ADC via DMA.
//
// This should get bEMF measurements (thru DMA) from the PWM driving a motor
// at changing speeds and send it off-board.
//
// Interface: testADC.py
#elif defined(__TEST_ADC_VIA_DMA)

#include "init.h"
#include "init_default.h"
#include "dma_alloc.h"
#include "uart.h"
#include "pwm.h"
#include "utils.h"

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupUART();
    SetupPWM();
    SetupDMA();
    SetupADC();
    SwitchClocks();
    LED_1 = 1;    

    /* Declarations */
    unsigned int i, j;
    int *Vm = (int *)(DMA_BASE + DMA_START_BUFA);
    
    /* Program */
    while(1){

        // Wait until a 1 arrives
        while(!DataRdyUART2());
        if (ReadUART2() == 1) {

            _ADON = 1;

            // Run a staircase of 0, 25, 50, 75, 100 on the PWM with each step
            // taking .5s and then cycle
            for (i=0; i<=4; i++) {
                SetDCMCPWM(2, (unsigned int)(2.0 * i * 25/100.0 * PTPERvalue), 0);
                for (j=0; j<1000; j++) { delay_us(500); }   // Waste approx .5s
            }

            // Wait until one-shot DMA operation ends
            while(DSADR < 2046);

            // Send collected bEMF data offboard
            for (i=0; i<DMA_RAM_SIZE; i++) {
                while(U2STAbits.UTXBF);
                WriteUART2((unsigned char)(((Vm[i] >> 5) & 0x001F) | 0x0080));
                while(U2STAbits.UTXBF);
                WriteUART2((unsigned char)(Vm[i] & 0x001F));
            }

            // Finalize transmission
            while(U2STAbits.UTXBF);
            WriteUART2(0x0060);

        }
    }

    return 0;
}


// Tests the DataFlash Memory.
//
// This will write a phrase starting at byte 0 of page 0 through buffer 1 and
// then read it and send it back.
// 
// Interface: testDFMEM.py
#elif defined(__TEST_DFMEM)

#include "init.h"
#include "init_default.h"
#include "utils.h"
#include "dfmem.h"

int main (void)
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupUART();
    dfmemSetup();
    SwitchClocks();
    LED_1 = 1;

    #define DFMEM_PAGESIZE   528

    /* Declarations */
    unsigned int page, byte = 0, buffer = 1, i;
    unsigned char phrase[] = "Just what do you think you're doing, Dave?\n",
                  itsaid[DFMEM_PAGESIZE];
    
    /* Program */
    while (1)
    {
        // Wait for command
        while(!U2STAbits.URXDA);
        page = U2RXREG;

        //dfmemErasePage(page);
        //dfmemEraseBlock(page);
        dfmemEraseSector(page);
        //dfmemEraseChip(); // faulty on 4MB chips
        dfmemWriteBuffer(phrase, sizeof(phrase), byte, buffer);
        dfmemWriteBuffer2MemoryNoErase(page, buffer);
        //dfmemWrite(phrase, sizeof(phrase), page, byte, buffer);
        dfmemRead(page, byte, DFMEM_PAGESIZE, itsaid);
        buffer = ~buffer;

        // Send back what it said
        for (i = 0; i < DFMEM_PAGESIZE; i++)
        {
            while(U2STAbits.UTXBF);
            U2TXREG = itsaid[i];
        }
        while(U2STAbits.UTXBF);
        U2TXREG = '\n';
    };


    return 0;
}


// Tests the Omnivision Camera with the DataFlash Memory.
//
// 
// 
// Interface: testOVCAMwDFMEM.py
#elif defined(__TEST_OVCAM_VIA_DFMEM)

#include "init_default.h"
#include "utils.h"
#include "dfmem_devel.h"
#include "ovcam.h"
#include "stopwatch.h"
#include "xl.h"
#include "gyro.h"

int main (void)
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupUART();
    dfmemSetup();
    SwitchClocks();
    swatchSetup();
    xlSetup();
    gyroSetup();    
    ovcamSetup();
    LED_1 = 1;    

    #define IMCOLS      176  
    #define IMROWS      1
    #define IMROWSTART  60
    #define PAGESIZE    176
    #define FRAMES      240

    /* Declarations */
    unsigned int i, rowcnt, imcnt, page, buffer = 1;
    unsigned char image[IMROWS][IMCOLS], contents[PAGESIZE];
    unsigned long time_elapsed;
    unsigned char *time_elapsed_str = (unsigned char *)&time_elapsed;
    unsigned char *xlStrData, *gyroStrData;

    /* Program */
    while (1)
    {
        LED_1 = 1;    

        // Wait for command
        while(!U2STAbits.URXDA);
        if (U2RXREG == 1)
        {
            //dfmemEraseChip();
            page = 0;
            swatchReset();
            swatchTic();

            // Provide image resolution and quantity
            while(U2STAbits.UTXBF);
            U2TXREG = IMCOLS;
            while(U2STAbits.UTXBF);
            U2TXREG = IMROWS;
            while(U2STAbits.UTXBF);
            U2TXREG = FRAMES;

            LED_1 = 0;


            for (imcnt = 0; imcnt < FRAMES; imcnt++)
            {
                // Throw out frame fraction
                ovcamWaitForNewFrame();

                // Send rows to RAM
                while (rowcnt < IMROWS) rowcnt++;
                ovcamGetRow(contents);

                // Get timestamp
                time_elapsed = swatchToc();
                for (i = 0; i < sizeof(long); i++)
                {
                    contents[160+i] = time_elapsed_str[i];
                }

                // Get IMU data
                xlStrData = xlReadXYZ();
                for (i = 0; i < 6; i++)
                {
                    contents[164+i] = xlStrData[i];
                }
                gyroStrData = gyroReadXYZ();
                for (i = 0; i < 6; i++)
                {
                    contents[170+i] = gyroStrData[i];
                }

                //dfmemWriteBuffer (image[0], PAGESIZE, 0, buffer);
                //dfmemWriteBuffer2MemoryNoErase (page, buffer);
                dfmemWrite(contents, PAGESIZE, page, 0, buffer);
                page++;
                buffer = ~buffer;
            }
    
            LED_2 = 1;

            for (page = 0; page < FRAMES; page++) 
            {
                dfmemRead(page, 0, PAGESIZE, contents);
    
                // Send back page contents
                for (i = 0; i < PAGESIZE; i++) {
                    while(U2STAbits.UTXBF);
                    U2TXREG = contents[i];
                }
            }

            LED_2 = 0;
        }
    }

    return 0;
} 


// Tests writing and reading from memory through DMA
//
// TODO (fgb) : Not working yet
//
// Interface: testDFMEM.py
#elif defined(__TEST_DFMEM_VIA_DMA)

#include "dfmem_dma.h"
#include "dma_alloc.h"
#include "init_default.h"
#include "utils.h"

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupUART();
    dfmemSetup(1);    
    SwitchClocks();
    LED_1 = 1;

    /* Declarations */
    unsigned int page, byte = 0, i;
    //unsigned char *contents_to = (unsigned char *)(DMA_BASE + DMA_START_BUF_DFMEM_TX),
    //              *contents_from = (unsigned char *)(DMA_BASE + DMA_START_BUF_DFMEM_RX);
    
    /* Program */
    while(1)
    {
        // Wait for command
        while(!U2STAbits.URXDA);
        page = U2RXREG;

        LED_2 = 1;
        
        // Send string down the drain
        //contents    = "   Just what do you think you're doing, Dave?\n";
        contents_to[0] = 0x82;
        contents_to[1] = (page >> 6) & 0b111111;
        contents_to[2] = ((page << 2) & 0b11111100) + ((byte >> 8) & 0b11);
        contents_to[3] = byte & 0xFF;
        contents_to[4] = 'H';
        contents_to[5] = 'W';
        contents_to[6] = '\n';
        
        while(!dfmemIsReady());            

        dfmemSelectChip();

        //DMA1CONbits.CHEN = 1;
        //DMA0CONbits.CHEN = 1;
        DMA0REQbits.FORCE = 1;
        //while(DMA0CONbits.CHEN);
        delay_ms(2000);

        dfmemDeselectChip();
        
        LED_1 = 0;

        // Get string from the sky
        //while(!dfmemIsReady());

        //dfmemSelectChip();

        //dfmemWriteByte(0xD2);
        //dfmemWriteByte((page >> 6) & 0b111111);
        //dfmemWriteByte(((page << 2) & 0b11111100) + ((byte >> 8) & 0b11));
        //dfmemWriteByte(byte & 0xFF);
        //
        //dfmemWriteByte(0x00); // 4 don't care bytes
        //dfmemWriteByte(0x00);
        //dfmemWriteByte(0x00);
        //dfmemWriteByte(0x00);

        //DMA1CONbits.CHEN = 1;
        //DMA1REQbits.FORCE = 1;
        //while(DMA1CONbits.CHEN);

        //dfmemDeselectChip();

        //// Send back what it said
        //for (i = 0; i < sizeof(contents_from); i++)
        //{
        //    while(U2STAbits.UTXBF);
        //    U2TXREG = contents_from[i];
        //}

        LED_2 = 0;            
    }

    return 0;
}


// Tests stopwatch.
//
// Sends back the time elapsed it calculates after 2 seconds of delay
//
// Interface: testSWATCH.py
#elif defined(__TEST_STOPWATCH)

#include "init_default.h"
#include "utils.h"
#include "stopwatch.h"

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();    
    SetupUART();
    SwitchClocks();
    swatchSetup();    
    LED_1 = 1;

    /* Declarations */
    unsigned long time_elapsed;
    unsigned char *time_elapsed_str = (unsigned char *)&time_elapsed, i;

    /* Program */
    while(1)
    {
        // Wait for command
        while(!U2STAbits.URXDA);
        if (U2RXREG == 1)
        {
            swatchReset(); // reset to 0
            
            swatchTic();

            swatchDelayUs(1000000); // delay 1 sec
            swatchDelayMs(1000);    // delay 1 sec
            
            time_elapsed = swatchToc(); // ~2,000,000
            
            // Send back time elapsed
            for (i = 0; i < sizeof(long); i++)
            {
                while(U2STAbits.UTXBF);
                U2TXREG = time_elapsed_str[i];
            }
            while(U2STAbits.UTXBF);
            U2TXREG = '\n';
        }
    }

    return 0;
}


// Tests the accelerometers.
//
// Sets up and sends back a reading from the accelerometers.
// 
// Interface: testIMU.py
#elif defined(__TEST_ACCEL)

#include "init.h"
#include "init_default.h"
#include "utils.h"
#include "xl.h"

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupUART();
    SwitchClocks();
    xlSetup();
    LED_1 = 1;

    /* Declarations */
    unsigned char xldata[3*sizeof(int)], i;
    
    /* Program */
    while(1){

        delay_ms(100);

        // read out data from accelerometer in raw string format
        xlGetXYZ(xldata);
        
        // Send back page contents
        for (i = 0; i < sizeof(xldata); i++) {
            while(U2STAbits.UTXBF);
            U2TXREG = xldata[i];
        }
    }

    return 0;
}


// Tests the gyroscopes.
//
// Sets up and sends back a reading from the gyroscopes.
// 
// Interface: testIMU.py
#elif defined(__TEST_GYRO)

#include "init.h"
#include "init_default.h"
#include "utils.h"
#include "gyro.h"

int main ( void )
{

    /* Initialization */
    SetupClock();
    SetupPorts();
    SetupUART();
    SwitchClocks();
    //gyroSetup();
    LED_1 = 1;

    /* Declarations */
    unsigned char gyrodata[3*sizeof(int)], i;
    
    /* Program */
    while(1){

        U2MODEbits.UARTEN = 0;
        gyroSetup();
        
        delay_ms(100);

        // read out data from gyroscope in raw string format
        gyroGetXYZ(gyrodata);

        I2C2CONbits.I2CEN = 0;
        SetupUART(); 

        delay_ms(100);

        // Send back page contents
        for (i = 0; i < sizeof(gyrodata); i++) {
            while(U2STAbits.UTXBF);
            U2TXREG = gyrodata[i];
        }
    }

    return 0;
}


#endif
