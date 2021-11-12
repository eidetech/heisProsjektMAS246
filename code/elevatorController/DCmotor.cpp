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

// Turn motor off
void DCmotor::motorOff()
{
  digitalWrite(DECAY, HIGH); 
  digitalWrite(PHASE, LOW);
  analogWrite(ENABLE, 0);
}

