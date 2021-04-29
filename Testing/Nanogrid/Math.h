#include "Arduino.h"

#ifndef MATH_H

float fcos(float deg);
float fsin(float deg);
float facos(float val);
float fasin(float val);

float getPanelTilt(int16_t n_day, int16_t n_min, float lat);
float getPanelAzimuth(int16_t n_day, int16_t n_min, float lat);


#endif