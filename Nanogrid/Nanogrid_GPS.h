#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include <TimeLib.h>
#include "Constants.h"

#ifndef __NANOGRID_GPS_H__


enum GPS_Status {
    NO_FIX,
    HAS_FIX
};


typedef union __GPS_Data__ {
    uint8_t byteAccess[7];
    struct Data
    {
        int8_t status;
        int16_t lat;
        int16_t min;
        uint16_t day;
    } data;

} GPS_Data;


class Nanogrid_GPS{

    public:
        Nanogrid_GPS();
        void waitForFix();
        void update();
        uint8_t getStatus();

        int16_t getLat();
        int16_t getMin();
        uint16_t getDay();

    private:
        GPS_Data gpsData;
        Adafruit_GPS GPS;
        SoftwareSerial serial;

};


#endif
