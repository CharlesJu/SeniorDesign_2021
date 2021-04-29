#include "Math.h"

float fcos(float deg){
    return (float) cos((PI/180)*deg);
}

float fsin(float deg){
    return (float) sin((PI/180)*deg);
}

float facos(float val){
    return (float) acos(val)*180/PI;
}

float fasin(float val){
    return (float) asin(val)*180/PI;
}

float getPanelTilt(int16_t n_day, int16_t n_min, float lat){
    float delta = 23.45 * fsin(360*(n_day + 284)/365);
    float omega = n_min / 4;

    return fasin(fcos(lat)*fcos(delta)*fcos(omega) + fsin(lat)*fsin(delta));

}

float getPanelAzimuth(int16_t n_day, int16_t n_min, float lat){
    float delta = 23.45 * fsin(360*(n_day + 284)/365);
    float tilt = getPanelTilt(n_day, n_min, lat);

    return facos((fsin(tilt)*fsin(lat) - fsin(delta))/(fcos(tilt)*fcos(lat)));
}