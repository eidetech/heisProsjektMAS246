#include "Emergency.h"  
#include "Arduino.h"

Emergency::Emergency()
{
    pinMode(ENCODER_BTN, INPUT);
	attachInterrupt(digitalPinToInterrupt(ENCODER_BTN),readMecanicalEncoder_ISR, CHANGE);
}
	
Emergency::~Emergency()
{
	
}