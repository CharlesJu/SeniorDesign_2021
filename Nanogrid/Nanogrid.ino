#include "Nanogrid.h"
#include "PID.h"
#include "MotorControl.h"


// PID Constants and Setup

float kP = 0.1;
float kI = 0;
float kD = 0;
int enc_value;
float motor_power;
PID motor_pid(kP, kI, kD);

void setup() {

  // Motor Setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);



  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // motorTest();
  enc_value = analogRead(ENC);
  motor_power = motor_pid.get(enc_value, 500);
  char tbs[32];
  sprintf(tbs, "Motor: %d\tCurrent Angle: %u",(int)motor_power*100, enc_value);
  Serial.println(tbs);
}
