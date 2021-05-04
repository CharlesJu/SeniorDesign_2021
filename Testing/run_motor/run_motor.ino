#include "MotorControl.h"

#define direction -1

void setup(){
    
}

void loop(){
    setMotorSpeed(direction * 255);
}