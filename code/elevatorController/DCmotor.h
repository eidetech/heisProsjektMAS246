#include "Arduino.h"

#define ENABLE 7
#define PHASE 6
#define DECAY 5

enum direction
{
    UP = HIGH,
    DOWN = LOW
};

class DCmotor
{
private:
    
public:
    // Constructor
    DCmotor();

    // Destructor
    ~DCmotor();

    // Set motor PWM
    void setMotorSpeed(int pwm, direction dir);

    // Turn motor off
    void motorOff();
};
