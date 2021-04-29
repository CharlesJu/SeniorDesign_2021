#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include "Nanogrid.h"

#ifndef GPS_H

typedef struct{
    float lat;
    float time;
    uint8_t lock;
} GPS_Values;


class GPS{

    public:
        GPS();

        void reset();
        

}

#endif