/*
 * Testing platform:
 * Uncomment only the main() that includes the test you'd like to perform
 * 
 * Created on 2010-2-25 by fgb
 */

#include "init.h"


// Testing the clock setup procedure:
// This should light up the power LED once the initialization routines finish executing.

// int main ( void )
// {
// 
//     /* Initialization */
//     SetupClock();
//     SetupPorts();  
//     SwitchClocks();
// 
//     /* Program */
//     while(1){}
// 
//     return 0;
// }


// Testing the delay subroutine:
// This should toggle the error LED every half second.

// int main ( void )
// {
// 
//     /* Initialization */
//     SetupClock();
//     SetupPorts();    
//     SwitchClocks();
// 
//     /* Declarations */
//     unsigned int i;    
// 
//     /* Program */
//     while(1){
//     
//         asm volatile("btg   LATF, #1");
//         for (i=0; i<1000; i++) { Delay_us(500); }   // Waste approximatelly .5s 
//     
//     }
// 
//     return 0;
// }


// Testing the battery supervisor interrupt:
// This should toggle 5 times the error LED (every .5s) once the voltage to the board falls below the supervisor threshold.

// int main ( void )
// {
// 
//     /* Initialization */
//     SetupClock();
//     SetupPorts();
//     SetupInterrupts();    
//     SwitchClocks();
// 
//     /* Program */
//     while(1){}
// 
//     return 0;
// }


// Testing the UART port:
// This should send back whatever it receives, blocking the flow until it receives a byte or sends it back.
// Related python interface: testUART.py

// int main ( void )
// {
// 
//     /* Initialization */
//     SetupClock();
//     SetupPorts();
//     SetupUART();   
//     SwitchClocks();
// 
//     /* Declarations */
//     unsigned char byte;   
// 
//     /* Program */
//     while(1){
//     
//         // Wait for a new byte
//         while(!DataRdyUART2());
//         byte = ReadUART2();
//         _RF1 = 1;        
// 
//         // Send back the same byte
//         while(U2STAbits.UTXBF);
//         WriteUART2(byte);
//         _RF1 = 0;
//     
//     }
// 
//     return 0;
// }


// Testing the Camera:
// This should send back the first 100 lines of a QQVGA picture
// Related python interface: testCamera.py

// int main ( void )
// {
// 
//     /* Initialization */
//     SetupClock();
//     SetupPorts();
//     SetupUART();
//     SetupI2C();    
//     SwitchClocks();
//     SetupCamera();
// 
//     /* Declarations */
//     #define IMCOLS 160
//     #define IMROWS 100
// 
//     unsigned int i, j, rowcnt;
//     unsigned char temp;
//     unsigned char image[IMROWS][IMCOLS];
//     
//     /* Program */
//     while(1){
//   
//         // Wait until a 1 arrives
//         while(!DataRdyUART2());
//         if (ReadUART2() == 1) {
//             _RF1 = 1;
// 
//             // Throw out frame fraction
//             while(VSYNC);
//             while(!VSYNC);
//   
//             // Send rows to RAM
//             rowcnt = 0;
//             while(rowcnt < IMROWS) {
//                 getRow(image[rowcnt]);
//                 rowcnt++;
//             }
//   
//             // Send the captured image off-board
//             for (i=0; i<IMROWS; i++) {
//                 for (j=0; j<IMCOLS; j++) {
//                     WriteUART2(image[i][j]);
//                     while(BusyUART2());
//                 }
//             }
// 
//             _RF1 = 0;
//         }
// 
//     }
// 
//     return 0;
// }


// Testing the PWM output:
// This should turn on the PWM output, incresing the duty cycle every .5s until starting again

// int main ( void )
// {
// 
//     /* Initialization */
//     SetupClock();
//     SetupPorts();
//     SetupPWM();   
//     SwitchClocks();
// 
//     /* Declarations */
//     unsigned int i, j;   
// 
//     /* Program */
//     while(1){
//     
//         // Run a staircase of 0, 25, 50, 75, 100 on the PWM with each step taking .5s and then cycle
//         for (i=0; i<=4; i++) {
//             SetDCMCPWM(2, (unsigned int)(2.0 * i * 25/100.0 * PTPERvalue), 0);
//             for (j=0; j<1000; j++) { Delay_us(500); }   // Waste approximatelly .5s
//         }    
//     }
// 
//     return 0;
// }

// Testing the ADC:
// This should get bEMF measurements from the PWM driving a motor at changing speeds and send it off-board
// Related python interface: testADC.py

//int main ( void )
//{
//
//    /* Initialization */
//    SetupClock();
//    SetupPorts();
//    SetupUART();
//    SetupPWM();
//    SetupADC();
//    SwitchClocks();
//
//    /* Declarations */
//    unsigned int i, j, Vm;   
//
//    /* Program */
//    while(1){
//    
//        // Wait until a 1 arrives
//        while(!DataRdyUART2());
//        if (ReadUART2() == 1) {
//
//            _ADON = 1;
//
//            // Run a staircase of 0, 25, 50, 75, 100 on the PWM with each step taking .5s and then cycle
//            for (i=0; i<=4; i++) {
//                SetDCMCPWM(2, (unsigned int)(2.0 * i * 25/100.0 * PTPERvalue), 0);
//                for (j=0; j<1000; j++) { Delay_us(500); }   // Waste approximatelly .5s
//
//                // Get bEMF and send it offboard
//                Vm = ADC1BUF0;
//                while(U2STAbits.UTXBF);
//                WriteUART2((unsigned char)(((Vm >> 5) & 0x001F) | 0x0080));
//                while(U2STAbits.UTXBF);
//                WriteUART2((unsigned char)(Vm & 0x001F));
//
//            }
//
//            // Finalize transmission
//            while(U2STAbits.UTXBF);
//            WriteUART2(0x0060);
//
//        }
//    }
//
//    return 0;
//}

// Testing DMA triggered by ADC:
// This script sends back the address the DMA is currently accessing in it's RAM space. 
// Related python interface: testDMAwADC.py

//int main ( void )
//{
//
//    /* Initialization */
//    SetupClock();
//    SetupPorts();
//    SetupUART();
//    SetupPWM();
//    SetupDMA();
//    SetupADC();
//    SwitchClocks();
//
//    /* Declarations */
//    unsigned int i, j, reg;   
//
//    /* Program */
//    while(1){
//
//        // Wait until a 1 arrives
//        while(!DataRdyUART2());
//        if (ReadUART2() == 1) {
//
//            _ADON = 1;
//
//            // Send latest DMA address accessed
//            reg = DSADR;
//            while(U2STAbits.UTXBF);
//            WriteUART2((unsigned char)(reg >> 8));
//            while(U2STAbits.UTXBF);
//            WriteUART2((unsigned char)(reg));
//
//        }
//    }
//
//    return 0;
//}

// Testing the ADC via DMA:
// This should get bEMF measurements (thru DMA) from the PWM driving a motor at changing speeds and send it off-board
// Related python interface: testADC.py

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

    /* Declarations */
    unsigned int i, j;
    int *Vm = DMA_BASE + DMA_START_BUFA;
    
    /* Program */
    while(1){

        // Wait until a 1 arrives
        while(!DataRdyUART2());
        if (ReadUART2() == 1) {

            _ADON = 1;

            // Run a staircase of 0, 25, 50, 75, 100 on the PWM with each step taking .5s and then cycle
            for (i=0; i<=4; i++) {
                SetDCMCPWM(2, (unsigned int)(2.0 * i * 25/100.0 * PTPERvalue), 0);
                for (j=0; j<1000; j++) { Delay_us(500); }   // Waste approximatelly .5s
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
