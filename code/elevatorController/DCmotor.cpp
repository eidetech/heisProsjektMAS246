#include "DCmotor.h"

// Constructor
DCmotor::DCmotor()
{
    pinMode(ENABLE, OUTPUT);
    pinMode(PHASE, OUTPUT);
    pinMode(DECAY, OUTPUT);
}

// Destructor
DCmotor::~DCmotor()
{
}

// Set motor PWM
void DCmotor::setMotorSpeed(int pwm, direction dir)
{
  digitalWrite(DECAY, LOW); 
  digitalWrite(PHASE, dir);
  analogWrite(ENABLE, pwm);
}
