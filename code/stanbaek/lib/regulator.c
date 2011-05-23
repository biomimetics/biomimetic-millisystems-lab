/*
 * Copyright (c) 2009 - 2010, Regents of the University of California
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
 * Regulator
 *
 * by Stanley S. Baek
 *
 * v.alpha
 *
 * Revisions:
 *  Stanley S. Baek      2009-10-30    Initial release
 *                      
 * 
 */


#include "controller.h"
#include "dsp.h"
#include "regulator.h"
#include "timer.h"
#include "utils.h"
#include "attitude.h"
#include "payload.h"
#include "radio.h"
#include "motor_ctrl.h"
#include "cmd_const.h"
#include "led.h"
#include "stopwatch.h"
#include "gyro.h"
#include "xl.h"
#include "dfmem.h"
#include "wii.h"
#include <stdlib.h>
#include <math.h>

#include "lcd.h"
#include <stdio.h>


#define DEGREE_PER_PIXEL    0.0390625       // (40/1024)
#define RADIAN_PER_PIXEL    0.000681769239  // (3.14159265/180)*(40/1024)
#define PI                  3.14159265
/*-----------------------------------------------------------------------------
 *          Static Variables
-----------------------------------------------------------------------------*/
typedef union {
    float fval;
    unsigned long lval;
    short sval[2];
    unsigned char cval[4];
} uByte4;

static union {
    struct {
        unsigned int page;
        unsigned int byte;
    } index;
    unsigned char chr_index[4]; 
} MemLoc;

CtrlPidParam yawPid, pitchPid;
DigitalFilter yawRateFilter, pitchRateFilter;

static unsigned char saveData2Flash = 0;
static unsigned char rcRunning = 0;

/*-----------------------------------------------------------------------------
 *          Declaration of static functions
-----------------------------------------------------------------------------*/

static void runWiiTracking(float roll, float pitch, float yaw, uByte4* yaw_ir, uByte4* pitch_ir);
static float runYawControl(float yaw);
static float runPitchControl(float pitch);

/*-----------------------------------------------------------------------------
 *          Public functions
-----------------------------------------------------------------------------*/

void rgltrSetup(float ts) {
    yawPid = ctrlCreatePidParams(ts);
    pitchPid = ctrlCreatePidParams(ts);
    yawRateFilter = NULL;
    pitchRateFilter = NULL;
}

unsigned char rgltrIsDataSaving(void) {
    return saveData2Flash;
}

void rgltrSetSaveData2Flash(unsigned int flag, unsigned int start_page) {

    saveData2Flash = (unsigned char)flag;
    MemLoc.index.page = start_page;
    MemLoc.index.byte = 0;

}

void rgltrSetYawRateFilter(unsigned char order, float* xcoeffs, float* ycoeffs) {

    yawRateFilter = dspCreateFilter(order, FILTER_TYPE_FLOAT, xcoeffs, ycoeffs);

} 


void rgltrSetPitchRateFilter(unsigned char order, float* xcoeffs, float* ycoeffs) {

    pitchRateFilter = dspCreateFilter(order, FILTER_TYPE_FLOAT, xcoeffs, ycoeffs);

} 

void rgltrSetPidYaw(float ref, float offset, float kp, float ki, float kd, float beta, float gamma) {
    
    ctrlSetPidParams(yawPid, ref, kp, ki, kd);
    ctrlSetPidOffset(yawPid, offset);
    ctrlSetRefWeigts(yawPid, beta, gamma);
    ctrlSetSaturation(yawPid, 100, -100);

}

void rgltrSetPidPitch(float ref, float offset, float kp, float ki, float kd, float beta, float gamma) {
    
    ctrlSetPidParams(pitchPid, ref, kp, ki, kd);
    ctrlSetPidOffset(pitchPid, offset);
    ctrlSetRefWeigts(pitchPid, beta, gamma);
    ctrlSetSaturation(pitchPid, 100, 60);

}


void rgltrSetRemoteControlValues(float thrust, float steer) {
    ctrlSetPidOffset(pitchPid, thrust);
    ctrlSetPidOffset(yawPid, steer);
}


void rgltrSetAutoYawControl(unsigned char flag) {

    if (flag == 0) {
        ctrlStop(yawPid);
    } else {
        ctrlStart(yawPid);
    }
}

void rgltrSetAutoPitchControl(unsigned char flag) {

    if (flag == 0) {
        ctrlStop(pitchPid);
    } else {
        ctrlStart(pitchPid);
    }
}

void rgltrSetRemoteControl(unsigned char flag) {

    rcRunning = flag;

}

void rgltrRunController(void) {

    uByte4 time, thrust, steer, yaw, yaw_ref, pitch, pitch_ref, roll;
    uByte4 yaw_ir, pitch_ir;
    //uByte4 yaw_rate_filtered;

    const int kDataLength = 42;
    static unsigned char buf_index = 1;
    unsigned char buffer[kDataLength];
    
    int i;

    time.lval = swatchTic();
    yaw.fval = attGetYaw();
    pitch.fval = attGetPitch();
    roll.fval = attGetRoll();
    
    runWiiTracking(roll.fval, pitch.fval, yaw.fval, &yaw_ir, &pitch_ir);

    steer.fval = runYawControl(yaw.fval);
    thrust.fval = runPitchControl(pitch.fval);

    mcSteer(steer.fval);
    mcThrust(thrust.fval);

    // yaw_rate_filtered.fval = dspGetLatestOutputValue(yawRateFilter);
    yaw_ref.fval = ctrlGetRef(yawPid);
    pitch_ref.fval = ctrlGetRef(pitchPid);

    if (saveData2Flash == 1) {
        for (i = 0; i < 4; i++) {
            buffer[i] = time.cval[i];
            buffer[i+4] = steer.cval[i];
            buffer[i+8] = thrust.cval[i];
            buffer[i+12] = yaw.cval[i];
            buffer[i+16] = pitch.cval[i];
            buffer[i+20] = yaw_ir.cval[i];
            buffer[i+24] = yaw_ref.cval[i];
            buffer[i+28] = pitch_ir.cval[i];
            buffer[i+32] = pitch_ref.cval[i];

        }

        gyroDumpData(buffer+36);

        dfmemWriteBuffer(buffer, kDataLength, MemLoc.index.byte, buf_index); 
        MemLoc.index.byte += kDataLength;
        if (MemLoc.index.byte + kDataLength > 528) { 
            dfmemWriteBuffer2MemoryNoErase(MemLoc.index.page++, buf_index);
            MemLoc.index.byte = 0;
            buf_index ^= 0x01;      // toggle buffer index between 0 and 1
        }

    }
}


/*-----------------------------------------------------------------------------
 * ----------------------------------------------------------------------------
 * The functions below are intended for internal use, i.e., private methods.
 * Users are recommended to use functions defined above.
 * ----------------------------------------------------------------------------
-----------------------------------------------------------------------------*/

static void runWiiTracking(float roll, float pitch, float yaw, uByte4* yaw_ir, uByte4* pitch_ir) {

    WiiBlob blobs[4];
    char target_index; 
    static unsigned char target_found = 0;
    static float yaw_wii = 0;
    static float yaw_old = 0;
    
    float pitch_org_ref = 45.0*PI/180;
    static float pitch_wii = 0;
    float yaw_delta;

    float x, y;
    
    target_index = wiiFindTarget(blobs);

    if (target_index < 0) { // target not found
        LED_BLUE = 0;
        if (target_found == 1) {  // target lost
            yaw_delta = yaw - yaw_old;
            if ((yaw_delta > 0 && yaw_wii < 0) || (yaw_delta < 0 && yaw_wii > 0)) {
                // if the bird is turning the other direction of the target
                ctrlSetRef(yawPid, ctrlGetRef(yawPid) - 2*yaw_delta);
            }
            // if the bird loses the target, just fly at the normal pitch.
            ctrlSetRef(pitchPid, pitch_org_ref);
        }

    } else {
        LED_BLUE = 1;
        target_found = 1;
        // The following eq depends on the orientation of wii camera. 
        x = (512 - blobs[(unsigned char)target_index].x)*RADIAN_PER_PIXEL;
        y = (384 - blobs[(unsigned char)target_index].y)*RADIAN_PER_PIXEL;
        yaw_wii = x*cos(roll) + y*sin(roll);
        pitch_wii = -x*sin(roll) + y*cos(roll);
        ctrlSetRef(yawPid, yaw + yaw_wii);
        ctrlSetRef(pitchPid, pitch + pitch_wii);
    }

    yaw_old = yaw;

    yaw_ir->fval = yaw_wii;
    pitch_ir->fval = pitch_wii;


}


// If Remote Control is used, then the offset of the control parameters
// will be used. It is user's reponsibility to set PID parameters 0 for
// Remote Control to behave correctly.
static float runYawControl(float yaw) {

    float u;

    if (rcRunning) {
        return ctrlGetPidOffset(yawPid);
    } else if (ctrlIsRunning(yawPid) == 0) {
        return 0;
    } else {
        // take care of motor backlash by scaling u.
        // the dead zone of tail prop is +-15% duty cycle.
        u = ctrlRunPid(yawPid, yaw, yawRateFilter);

        if (u > 5) {
            return u*0.85 + 15;
        } else if (u < -5) {
            return u*0.85 - 15;
        } else {
            return u;
        }
    }    

}


static float runPitchControl(float pitch) {

    if (rcRunning) {
        return ctrlGetPidOffset(pitchPid);
    } else if (ctrlIsRunning(pitchPid) == 0) {
        return 0;
    } else {
        return ctrlRunPid(pitchPid, pitch, pitchRateFilter);
    }
}







