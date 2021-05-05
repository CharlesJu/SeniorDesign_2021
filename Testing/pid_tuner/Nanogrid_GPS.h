#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include <TimeLib.h>
#include "Constants.h"

#ifndef __NANOGRID_GPS_H__
#define __NANOGRID_GPS_H__

enum GPS_Status {
    NO_FIX,
    HAS_FIX
};


typedef union __GPS_Data__ {
    struct Data
    {
        int8_t status;
        float lat;
        float lon;
        time_t time;
    } data;

} GPS_Data;


class Nanogrid_GPS{

    public:
        Nanogrid_GPS( Print &print);

        void setup();

        void waitForFix();
        void update();
        void pollData();

        uint8_t getStatus();
        float getLat();
        float getLon();
        time_t getTime();
        // int16_t getMin();
        // uint16_t getDay();


    private:
        GPS_Data gpsData;
        Adafruit_GPS GPS;
        SoftwareSerial serial;
        Print* printer;

};


#endif
