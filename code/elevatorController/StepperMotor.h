#define SDI_pin 31
#define SCK_pin 32
#define CS_pin 33
#define LDAC_pin 30
#define EnableA 69
#define EnableB 67
#define PhaseA 68
#define PhaseB 66

class StepperMotor
{
private:
    float steppingDelay = 10.0;
    unsigned long lastMillis = 0;
    unsigned long currentMillis = 0;
    int stepCount;
    int stepSequence = 1;
public:
    StepperMotor();
    ~StepperMotor();

    void moveForward(int steps);
    void moveBackward(int steps);
};
