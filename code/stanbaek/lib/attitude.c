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
 * This module is to estimate orientation of a robot
 *
 * by Stanley S. Baek
 *
 * v. beta
 *
 * Revisions:
 *  Stanley S. Baek      2010-08-27    Initial release
 *                      
 * 
 */


#include "attitude.h"
#include "xl.h"
#include "gyro.h"
#include "wii.h"
#include <math.h>


/*-----------------------------------------------------------------------------
 *          Static Variables
-----------------------------------------------------------------------------*/

// State parameters
static union {
    struct {
        // Euler angle 3-2-1
        float phi;      // roll
        float theta;    // pitch
        float psi;      // yaw
    } fdata;
    float   farray[3];
    unsigned char carray[12];
} Pose;

static float samplePeriod = 0;
static unsigned char isRunning = 0;


/*-----------------------------------------------------------------------------
 *      Declaration of static functions (private functions)
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 *          Public functions
-----------------------------------------------------------------------------*/

void attSetup(float ts) {
    
    samplePeriod = ts;

    // initial values of roll, pitch, and yaw.
    Pose.fdata.phi = 0.0;
    Pose.fdata.theta = 0.0;
    Pose.fdata.psi = 0.0;
}

float attGetPitch(void) {
    return Pose.fdata.theta;
}

float attGetRoll(void) {
    return Pose.fdata.phi;
}

float attGetYaw(void) {
    return Pose.fdata.psi;
}

float* attGetPose(void) {
    return Pose.farray;
}

unsigned char attIsRunning(void) {
    return isRunning;
}

void attSetEstimateRunning(unsigned char flag) {

    isRunning = flag;
    Pose.fdata.phi = 0.0;
    Pose.fdata.theta = 0.0;
    Pose.fdata.psi = 0.0;

}


void attReadSensorData(void) {
    gyroReadXYZ();  // 255 us
    xlReadXYZ();    // 250 us
    wiiReadData();  // ~400 us 
}


void attEstimatePose(void) {

    float dphi, dtheta, dpsi;
    float rate[3];
    float wx, wy, wz;
    float sin_phi, tan_theta, cos_phi, cos_theta, temp;

    gyroGetRadXYZ(rate);  // 50 us
    
    // coordinate conversion for Modified I-Bird
    wx = rate[0];
    wy = rate[1];
    wz = rate[2];

    // it takes ~27us for the following four lines 
    sin_phi = sin(Pose.fdata.phi);
    cos_phi = cos(Pose.fdata.phi);
    cos_theta = cos(Pose.fdata.theta);
    tan_theta = tan(Pose.fdata.theta);
        
    // it takes ~41us for the following four lines     
    temp = wy*sin_phi + wz*cos_phi;
    dphi = wx + temp*tan_theta;
    dtheta = wy*cos_phi - wz*sin_phi;
    dpsi = temp/cos_theta;
    
    // it takes ~42us for the following three lines     
    Pose.fdata.phi += dphi*samplePeriod;
    Pose.fdata.theta += dtheta*samplePeriod;
    Pose.fdata.psi += dpsi*samplePeriod;
    
}







