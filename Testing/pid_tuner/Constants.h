#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define IN1 7
#define IN2 8
#define ENA 9
#define ENC 0
#define GPS_TX 2
#define GPS_RX 4
#define GPS_FIX 3

#define HOUR_OFFSET -8

#define ENC_DEFAULT 35

#define IMU_I2C_ID -1
#define IMU_I2C_ADDRESS 0x28
#define BNO055_SAMPLERATE_DELAY_MS (100)

// DEBUG
#define GPSDEBUG false
#define ENCDEBUG false
#define IMUDEBUG true

// Stat
#define GPSECHO false
#define GPSSTAT false
#define ENCSTAT false
#define IMUSTAT false
#endif