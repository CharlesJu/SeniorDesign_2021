#include "Constants.h"
#include "MotorControl.h"
#include "PID.h"

uint16_t enc_val;
float p = 10;
float i = 0.05;
float d = -5;
float motor_power;
PID motor_pid(p, i, d);

void setup(){
    Serial.begin(115200);
    setMotorSpeed(-255);
    delay(5000);
    setMotorSpeed(0);
    // enc_val = analogRead(ENC);
    // motor_power = motor_pid.get(enc_val, 900);
    // while(abs(motor_pid.getErr()) > 20){
    //     setMotorSpeed(255);
    //     enc_val = analogRead(ENC);
    //     Serial.println(enc_val);
    // }
    // Serial.println("End Setup");
    // delay(5000);
    
}

void loop(){
    enc_val = analogRead(ENC);
    motor_power = motor_pid.get(enc_val, 600);
    setMotorSpeed(motor_power);
    Serial.println(enc_val);

}