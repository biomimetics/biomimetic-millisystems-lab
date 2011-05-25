/******************************************************************************
* Date: 2010-07-08
* Author: stanbaek
*******************************************************************************/

#include "p33Fxxxx.h"
#include "init_default.h"
#include "timer.h"
#include "ports.h"
#include "cmd.h"
#include "radio.h"
#include "xl.h"
#include "gyro.h"
#include "utils.h"
#include "led.h"
#include "attitude.h"
#include "stopwatch.h"


int main(void) {

    SetupClock();
    SwitchClocks();
    SetupPorts();
    swatchSetup();
    radioSetup(80, 10);   // tx_queue = 80, rx_queue = 10
    cmdSetup();

    xlSetup();
    xlSetRange(16);
    xlSetOutputRate(0, 0x0c); //400Hz
    gyroSetup();

    int i;

    for (i = 0; i < 6; i++) {
        LED_GREEN = ~LED_GREEN;
        delay_ms(50);
        LED_RED = ~LED_RED;
        delay_ms(50);
        LED_BLUE = ~LED_BLUE;
        delay_ms(50);
    }

    LED_GREEN = 1;
    LED_RED = 1;
    LED_BLUE = 1;

    delay_ms(500);

    if(radioGetTrxState() == 0x16)  { 
        LED_GREEN = 0;
        LED_RED = 0;
        LED_BLUE = 0;
    }

    swatchReset();

    while(1) {
        cmdHandleRadioRxBuffer();
    }
    
}




