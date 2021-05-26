#include "Encoder.h"

float getAngle(){
    uint16_t value = analogRead(ENC);
    return (value/1024.0) * 360.0;

}