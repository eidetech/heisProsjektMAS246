#include "FloorButtons.h"
#include "Arduino.h"

FloorButton::FloorButton()
{    
}

CabButtons::~CabButtons()
{
}


int Floorbuttons::readFloorBtn(int readFloorBtn)
{
    input = Serial.read();
    return input;
}

enum Floobuttons::readUpDown(enum readUporDown)
{
    input = Serial.read();
    return input;
}


int FloorButtons::display()
{
    Serial.println(readUpDown);
    Serial.println(readFloorBtn)
}


