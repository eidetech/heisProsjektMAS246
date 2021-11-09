class PID
{
private:
    static void readEncoder();

public:

    long prevT = 0;
    int posPrev = 0;

    static volatile int pos_i;
    static volatile float velocity_i;
    static volatile long prevT_i;

    float v1Filt = 0;
    float v1Prev = 0;
    float v2Filt = 0;
    float v2Prev = 0;

    float eintegral = 0;

    int pos = 0;
    float velocity2 = 0;

    float vt;
    
    PID();
    ~PID();

    float PIDcalc();

    
    
};