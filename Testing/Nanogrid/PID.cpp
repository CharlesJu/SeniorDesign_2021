#include "PID.h"

PID::PID(float kP, float kI, float kD)
{
    vals.kP = kP;
    vals.kI = kI;
    vals.kD = kD;
    vals.val = 0;
    vals.target = 0;
    vals.e_prev = 0;
    vals.e_diff = 0;
    vals.e_cur = 0;
    vals.e_tot = 0;
    vals.o_min = -1E30;
    vals.o_max = 1E30;
    float e_diff_prev = 0;
    short dT_cont = 0;
}

PID::PID(float kP, float kI, float kD, float min, float max)
{
    vals.kP = kP;
    vals.kI = kI;
    vals.kD = kD;
    vals.val = 0;
    vals.target = 0;
    vals.e_prev = 0;
    vals.e_diff = 0;
    vals.e_cur = 0;
    vals.e_tot = 0;
    vals.o_min = min;
    vals.o_max = max;
    float e_diff_prev = 0;
    short dT_cont = 0;
}

void PID::update(float val, float target)
{
    //This needs to be update every loop
    vals.val = val;
    vals.target = target;
    if (target != vals.target)
    {
        reset();
    }
    else
    {
        vals.e_cur = target - val;
        vals.e_diff = vals.e_prev - vals.e_cur;
        vals.e_tot += vals.e_cur;

        //Prevents I value Windup
        if ((vals.e_diff < vals.e_diff_prev + 0.005 || vals.e_diff > vals.e_diff_prev - 0.005) && vals.dT_cont < 501)
        {
            vals.dT_cont += 1;
        }
        else
        {
            vals.dT_cont = 0;
            vals.e_tot = 0;
        }
    }
}

void PID::reset()
{
    vals.val = 0;
    vals.e_prev = 0;
    vals.e_diff = 0;
    vals.e_cur = 0;
    vals.e_tot = 0;
}

float PID::out()
{
    float v = vals.e_cur * vals.kP + vals.e_tot * vals.kI + vals.e_diff * vals.kD;

    if (v < vals.o_min)
    {
        v = vals.o_min;
    }
    else if (v > vals.o_max)
    {
        v = vals.o_max;
    }

    vals.e_prev = vals.e_cur;

    return v;
}

float PID::get(float val, float target)
{
    update(val, target);
    return out();
}

float PID::getVal()
{
    return vals.val;
}

float PID::getErr()
{
    return vals.e_cur;
}

float PID::getPrevErr()
{
    return vals.e_diff + vals.e_cur;
}

float PID::getTotErr()
{
    return vals.e_tot;
}
