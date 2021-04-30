#include "Constants.h"
#include "MotorControl.h"
#include "PID.h"
#include "Nanogrid_GPS.h"
#include "SolarPosition.h"

uint16_t enc_val;
float p = 10;
float i = 0.05;
float d = -5;
float motor_power;
float target;
PID motor_pid(p, i, d);
Nanogrid_GPS gps(Serial);

void setup(){
    Serial.begin(115200);
    Serial.println("----- Begin Program -----");
    delay(1000);
    gps.setup();

    target = 100;

    // setMotorSpeed(-255);
    // delay(5000);
    // setMotorSpeed(0);
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

uint32_t timer = millis();

void loop(){
    enc_val = analogRead(ENC);
    motor_power = motor_pid.get(enc_val, target);
    setMotorSpeed(motor_power);


    gps.update();
    if (millis() - timer > 2000){
        timer = millis();
        gps.pollData();
        
        if(gps.getStatus() == HAS_FIX){
            SolarPosition_t position_data;
            SolarPosition pos(gps.getLon(), gps.getLat());
            position_data = pos.getSolarPosition(gps.getTime());

            target = (position_data.azimuth / 360.0) * 1024;
            
        } else {
            target = ENC_DEFAULT;
        }

        if(ENCSTAT)
                Serial.print("[ENC] Target: "); Serial.println(target);
        
    }
    

}