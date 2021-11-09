#define ENCA 21
#define ENCB 22


class PID
{
private:
    static void ISR_A();
    static void ISR_B();

    
public:
    
    PID();
    ~PID();
    static float PIDcalc();

    //static bool pinA, pinB;
    static volatile long encoderCount;
    static float theta, theta_prev, theta_d, RPM;
    static unsigned long t, t_prev;

    static float u, dt;

    static float e, e_prev, int_e, int_e_prev;

    static volatile long globalEncoderCounter;

    static int Kp, Ki, Kd;

};