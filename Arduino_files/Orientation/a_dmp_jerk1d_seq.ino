// This file gives both orientation(YPR) and displacement along XYZ axis 
// For visualizing in python, comment out the first serial.print lines in g_loop tab
// By default the angles(ypr) are in degrees & Distance in cm

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps_V6_12.h"  //changed to this version 10/04/19
#include "elapsedMillis.h"
 
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high
 
#define LED_PIN 13 
#define g 9.81
 
bool blinkState = false;
 
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float out[4];

//extra stuff
int IMU_CHECK_INTERVAL_MSEC = 10;
elapsedMillis sinceLastIMUCheck;
float global_yawval = 0.0; //contains most recent yaw value from IMU
int global_fifo_count = 0; //made global so can monitor from outside GetIMUHeadingDeg() fcn
 

 


 

 
