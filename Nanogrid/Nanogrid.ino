#include "Constants.h"
#include "MotorControl.h"
#include "PID.h"
#include "Nanogrid_GPS.h"
#include "SolarPosition.h"
#include "Nanogrid_IMU.h"

uint16_t enc_val;
float p = 25;
float i = 0.0075;
float d = 0.0;
float motor_power;
float adjusted_target;
float enc_target;
float gyro_value;

PID motor_pid(p, i, d);
Nanogrid_GPS gps(Serial);
Nanogrid_IMU imu_t(Serial);

void setup(){
    Serial.begin(115200);
    Serial.println("----- Begin Program -----");
    delay(1000);
    gps.setup();
    imu_t.setup();

    enc_target = ENC_DEFAULT;
    adjusted_target = ENC_DEFAULT;
    setMotorSpeed(255);
    delay(1000);
    setMotorSpeed(0);
    
    gps.waitForFix();
}

uint32_t timer_2s = millis();
uint32_t timer_100ms = millis();
uint32_t timer_5ms = millis();
uint32_t timer_5min = millis();

void loop(){

    gps.update();

    gyro_value = imu_t.getRotation();
    enc_val = analogRead(ENC);
    motor_pid.update(enc_val, adjusted_target);
    if(gyro_value > enc_target){
        adjusted_target = 360 - (gyro_value - enc_target);
    } else if (gyro_value < enc_target){
        adjusted_target = enc_target - gyro_value;
    } else {
        adjusted_target = enc_target;
    }
    

    adjusted_target = (adjusted_target/360.0) * 1024;

    if (abs(motor_pid.getErr()) > 2.5){

        motor_power = motor_pid.get(enc_val, adjusted_target);
        setMotorSpeed(motor_power);
    }

    if(millis() - timer_100ms > 100){
        timer_100ms = millis();
        if(IMUDEBUG){
            Serial.print("gyro_value: ");
            Serial.println(gyro_value);
            Serial.print("enc_target: ");
            Serial.println(enc_target);
            Serial.print("adjusted_target: ");
            Serial.println(adjusted_target);
            Serial.print("motor_power: ");
            Serial.println(motor_power);
            Serial.print("enc_val: ");
            Serial.println(enc_val);
            Serial.print("error ");
            Serial.println(motor_pid.getErr());

        }
    }

    if (millis() - timer_2s > 2000){
        timer_2s = millis();
        gps.pollData();
        
        if(gps.getStatus() == HAS_FIX){
            SolarPosition_t position_data;
            SolarPosition pos(gps.getLon(), gps.getLat());
            position_data = pos.getSolarPosition(gps.getTime());

            enc_target = position_data.azimuth + ENC_DEFAULT;
            
        } else {
            enc_target = ENC_DEFAULT;
        }

        if(ENCSTAT){
            Serial.print("[ENC] Target: "); Serial.println(enc_target);
        }
        
    }
    

}