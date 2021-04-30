#include "Arduino.h"
#include "MotorControl.h"
#include "Constants.h"

void setMotorSpeed(int16_t speed)
{
    uint8_t pwm_value = 0;

    speed *= MOTOR_DIRECTION;

    if (speed < 0)
    {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        if(speed < -255) speed = -255;
        pwm_value = (uint8_t) (-1*speed);
    }
    else if (speed > 0)
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        if(speed > 255) speed = 255;
        pwm_value = (uint8_t) (speed);
    }

    analogWrite(ENA, pwm_value);
}

void setMotorBreak()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
}

void motorTest()
{
    for (int i = 0; i < 255; ++i)
    {
        setMotorSpeed(255);
        delay(50);
    }
    setMotorSpeed(0);
    setMotorBreak();
    delay(1000);

    for (int i = 0; i > -255; --i)
    {
        setMotorSpeed(-255);
        delay(50);
    }
    setMotorSpeed(0);
    setMotorBreak();
    delay(1000);
}