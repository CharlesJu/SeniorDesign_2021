#include "Nanogrid.h"
#include "Arduino.h"
#include "MotorControl.h"

void setMotorSpeed(float speed)
{
    uint8_t pwm_value;
    if (speed < 0)
    {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        pwm_value = uint8_t(-speed * 255);
    }
    else if (speed > 0)
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        pwm_value = uint8_t(speed * 255);
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
        setMotorSpeed(float(i) / 255.0);
        delay(50);
    }
    setMotorSpeed(0);
    setMotorBreak();
    delay(1000);

    for (int i = 0; i > -255; --i)
    {
        setMotorSpeed(float(i) / 255.0);
        delay(50);
    }
    setMotorSpeed(0);
    setMotorBreak();
    delay(1000);
}