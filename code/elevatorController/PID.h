class PID
{
private:

public:

    long prevT = 0;
    int posPrev = 0;

    volatile int pos_i = 0;
    volatile float velocity_i = 0;
    volatile long prevT_i = 0;

    float v1Filt = 0;
    float v1Prev = 0;
    float v2Filt = 0;
    float v2Prev = 0;

    float eintegral = 0;

    int pos = 0;
    float velocity2 = 0;
    
    PID();
    ~PID();

    float PIDcalc();
    void readEncoder();
};