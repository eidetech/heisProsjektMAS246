#define ENCA 20
#define ENCB 21

class PID
{
private:
    static void readEncoder_ISR();
public:
    PID();
    ~PID();
    static float PIDCalc(float setPoint, float Kp, float Ki, float Kd, bool serialPlot);
};