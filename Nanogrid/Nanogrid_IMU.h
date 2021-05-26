
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#ifndef __COMPASS_H__
#define __COMPASS_H__


// #include <utility/imumaths.h>


class Nanogrid_IMU{
    public:
        Nanogrid_IMU( Print &print);
        float getRotation();
        void calibrate();
        void setup();
    
    private:
        Adafruit_BNO055 bno;
        Print* printer;
};


#endif