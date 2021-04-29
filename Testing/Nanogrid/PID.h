#ifndef PID_H

typedef struct{
    float kP;   float kI;   float kD;
    float val;  float target;
    float e_prev;   float e_diff;
    float e_cur;    float e_tot;
    float o_min;    float o_max;
    float e_diff_prev;  short dT_cont;
     
} PID_Values;

class PID{
    public:
        PID(float kP, float kI, float kD);
        PID(float kP, float kI, float kD, float min, float max);

        void update(float val, float target);
        void reset();
        float out();
        float get(float val, float target);
        float getVal();
        float getErr();
        float getPrevErr();
        float getTotErr();
    private:
        PID_Values vals;
};

#endif