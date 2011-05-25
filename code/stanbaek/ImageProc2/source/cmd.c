/***************************************************************************
* Name: cmd.c
* Desc: Receiving and transmitting queue handler
* Date: 2010-07-10
* Author: stanbaek
**************************************************************************/

#include "cmd.h"
#include "radio.h"
#include "utils.h"
#include "ports.h"
#include "gyro.h"
#include "xl.h"
#include "stopwatch.h"
#include "led.h"
#include "payload.h"
#include <stdlib.h>

#define MAX_CMD_FUNC_SIZE           0x10    // 0x00 - 0x0F
#define CMD_ECHO                    0x0F    // send back the received packet
#define CMD_GET_IMU_DATA            0x00    // get one imu data (3 gyro & 3 xl)


// use an array of function pointer to avoid a number of case statements
// MAX_CMD_FUNC_SIZE is defined in cmd_const.h
void (*cmd_func[MAX_CMD_FUNC_SIZE])(unsigned char, unsigned char, unsigned char*);


/*-----------------------------------------------------------------------------
 *          Declaration of static functions
-----------------------------------------------------------------------------*/

static void cmdGetImuData(unsigned char status, unsigned char length, unsigned char *frame);
static void cmdEcho(unsigned char status, unsigned char length, unsigned char *frame);
static void cmdNop(unsigned char status, unsigned char length, unsigned char *frame);


/*-----------------------------------------------------------------------------
 *          Public functions
-----------------------------------------------------------------------------*/
void cmdSetup(void) {

    unsigned int i;

    // initialize the array of func pointers with Nop()
    for(i = 0; i < MAX_CMD_FUNC_SIZE; ++i) {
        cmd_func[i] = &cmdNop;
    }

    cmd_func[CMD_ECHO] = &cmdEcho;
    cmd_func[CMD_GET_IMU_DATA] = &cmdGetImuData;

}


void cmdHandleRadioRxBuffer(void) {

    Payload pld;
    unsigned char command, status;  

    if ((pld = radioGetRxPayload()) != NULL) {
        status = payGetStatus(pld);
        command = payGetType(pld);      
        cmd_func[command](status, payGetDataLength(pld), payGetData(pld));
        payDelete(pld);
    } 

    return;
}



/*-----------------------------------------------------------------------------
 * ----------------------------------------------------------------------------
 * The functions below are intended for internal use, i.e., private methods.
 * Users are recommended to use functions defined above.
 * ----------------------------------------------------------------------------
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 *          IMU functions
-----------------------------------------------------------------------------*/

// return packet format:
// 4 bytes for time
// 6 bytes for xl data
// 6 bytes for gyro data
static void cmdGetImuData(unsigned char status, unsigned char length, unsigned char *frame) {

    unsigned int count;
    unsigned long tic;
    unsigned char *tic_char;
    Payload pld;
  
    LED_RED = 1;

    count = frame[0] + (frame[1] << 8);

    tic_char = (unsigned char*)&tic;
    swatchReset();
    tic = swatchTic();
    
    while (count) {

        pld = payCreateEmpty(16);  // data length = 16
        paySetData(pld, 4, tic_char);
        payAppendData(pld, 4, 6, xlReadXYZ());
        payAppendData(pld,10, 6, gyroReadXYZ());
        paySetStatus(pld, status);
        paySetType(pld, CMD_GET_IMU_DATA);

        radioSendPayload(pld);
        count--;
        delay_ms(9);   // ~10ms delay
        delay_us(195);
        tic = swatchTic();
    }

    LED_RED = 0;

}



/*-----------------------------------------------------------------------------
 *          AUX functions
-----------------------------------------------------------------------------*/
static void cmdEcho(unsigned char status, unsigned char length, unsigned char *frame) {
    radioSendPayload(payCreate(length, frame, status, CMD_ECHO));
}

static void cmdNop(unsigned char status, unsigned char length, unsigned char *frame) {
    Nop();
}



