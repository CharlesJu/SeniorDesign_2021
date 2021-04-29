#include "Arduino.h"

#ifndef SOLAR_H

    float getTilt(float lat, uint16_t n_day, uint16_t n_min);
    float getAzimuth(float lat, uint16_t n_day, uint16_t n_min);

    float getDecAngle(uint16_t n);
#endif