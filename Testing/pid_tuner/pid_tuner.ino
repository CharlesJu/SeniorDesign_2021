#include "PID.h"
#include "Constants.h"
#include "MotorControl.h"

float p = 10;
float i = 0.0001;
float d = -0.0;
float target = 30;
float adjusted_target;
uint16_t enc_val;
float motor_power;

PID motor_pid(p,i,d);

void setup(){
    Serial.begin(115200);
    setMotorSpeed(255);
    delay(10000);
}

void loop(){
    enc_val = analogRead(ENC);
    adjusted_target = (target/360.0) * 1024;
    motor_power = motor_pid.get(enc_val, adjusted_target);
    setMotorSpeed(motor_power);

    Serial.print("Target "); 
    Serial.print(adjusted_target);
    Serial.print(" ");
    Serial.print("Power "); 
    Serial.print(motor_power);
    Serial.print(" ");
    Serial.print("Encoder "); 
    Serial.println(enc_val);

}