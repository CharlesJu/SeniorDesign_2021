#include "Nanogrid.h"
#include "PID.h"
#include "MotorControl.h"
#include "Math.h"
#include "Encoder.h"

// PID Constants and Setup

float kP = 0.5;
float kI = 0;
float kD = 0;
float enc_value;
float motor_power;
PID motor_pid(kP, kI, kD);

float lat;
int16_t n_day;
int16_t n_min;
float tilt;
float azimuth;
float delta;
float omega;

void setup() {

  // Motor Setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  n_day = 116;
  n_min = 0;
  lat = 37.354107;

  Serial.begin(9600);
  Serial.println("Begin Program");

  motor_power = motor_pid.get(enc_value, 180);
  while(abs(motor_pid.getErr()) > 20){
    setMotorSpeed(1);
    enc_value = getAngle();
    Serial.println(enc_value);
  }

}

void loop() {
  
  // motorTest();
  
  enc_value = getAngle();
  motor_power = motor_pid.get(enc_value, 90);
  setMotorSpeed(motor_power);
  Serial.println(enc_value);

  // delay(1000);
  
  // char tbs[32];
  // sprintf(tbs, "Motor: %d\tCurrent Angle: %u",(int)motor_power*100, enc_value);
  
}
