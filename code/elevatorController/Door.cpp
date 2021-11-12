#include "Door.h"

Door::Door()
{
}

Door::~Door()
{
}

void Door::open()
{
    stepper.moveForward(doorMoveLength);
}

void Door::close()
{
    stepper.moveBackward(doorMoveLength);   
}

void Door::doorDisable()
{
    stepper.stepperDisable();
}