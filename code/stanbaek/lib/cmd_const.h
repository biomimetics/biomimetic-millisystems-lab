/******************************************************************************
* Name: cmd_const.h
* Desc: Commonly used command definitions are defined here.
* Date: 2010-07-10
* Author: stanbaek
******************************************************************************/
#ifndef __CMD_CONST_H
#define __CMD_CONST_H

#define MAX_CMD_FUNC_SIZE           0x40 // 0x00 - 0x3F

// CMD values of 0x00(0) - 0x3F(127) are defined here


#define CMD_SET_AUTO_CTRL           0x11
#define CMD_SET_REMOTE_CTRL         0x12

#define CMD_SET_PID_YAW             0x16
#define CMD_SET_PID_PITCH           0x18

#define CMD_SET_THRUST              0x1A
#define CMD_SET_STEER               0x1B
#define CMD_SET_STEER_MODE          0x1C
#define CMD_SET_RC_VALUES           0x1D

#define CMD_ECHO                    0x1F      // send back the received packet

// for IMU 
#define CMD_GET_IMU_DATA            0x20    // get one imu data (3 gyro & 3 xl)
#define CMD_GET_WII_DATA            0x22    // get one wii data (4 blobs)

#define CMD_RUN_GYRO_CALIB          0x24
#define CMD_GET_GYRO_CALIB_PARAM    0x25    // get gyroscope calibration offset

#define CMD_SET_SAVE_DATA_FLASH     0x26
#define CMD_SET_ESTIMATE_RUNNING    0x27

#define CMD_RESET_PACKET_SQN        0x2A
#define CMD_TX_SAVED_STATE_DATA     0x2B

//#define CMD_TX_DUTY_CYCLE           0x2C  // depricated


#define CMD_START_BODE              0x33
#define CMD_SET_YAW_RATE_FILTER     0x34
#define CMD_SET_PITCH_RATE_FILTER   0x35

#define CMD_ERASE_MEM_SECTOR        0x3A

#define CMD_RESET_STOPWATCH         0x3B

#define CMD_BASE_ECHO               0x3F        // send back the received packet



// CMD values of 0x80(128) - 0xEF(239) are reserved.
// CMD values of 0xF0(240) - 0xFF(255) are reserved for future use


#endif  // __CMD_CONST_H

