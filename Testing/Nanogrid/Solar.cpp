#include "Solar.h"
#include "Math.h"

float getTilt(float lat, uint16_t n_day, uint16_t n_min){
    float f = getDecAngle(n_day);
    float o = n_min / 4;

    return fasin(fcos(lat)*fcos(f)*fcos(o) + fsin(lat)*fsin(f));
}
float getAzimuth(float lat, uint16_t n_day, uint16_t n_min){
    float tilt = getTilt(lat, n_day, n_min);
    float f = getDecAngle(n_day);

    return facos( (sin(tilt)*sin(lat) - sin(f)) / (fcos(tilt)*cos(lat)));
}

float getDecAngle(uint16_t n){
    return 23.45 * fsin(360*(n+284.0)/365);
}