#include "Emergency.h"  
#include "Arduino.h"
#include "StateMachine.h"
#include "LED.h"

extern StateMachine stateMachine;
extern LED leds;

Emergency::Emergency()
{
    pinMode(ENCODER_BTN, INPUT);
	attachInterrupt(digitalPinToInterrupt(ENCODER_BTN),readMecanicalEncoder_ISR, CHANGE);
}
	
Emergency::~Emergency()
{
}

// readEncoder ISR
void Emergency::readMecanicalEncoder_ISR(){
  stateMachine.state = EMERGENCY;  
}
