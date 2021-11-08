#include "FloorButton.h"
#include "Arduino.h"

FloorButton::FloorButton()
{    
}

FloorButton::~FloorButton()
{
}

int Floorbutton::readFloorBtn()
{
    floorRequest = Serial.read();

    Serial.println(floorRequest);
    
    return floorRequest;
}

int FloorButton::readUpDown()
{
    input = Serial.read();
    if (input == 'U')
    {
        upRequests
        Serial.println("Going UP");
    }
    else if (input == 'D')
    {
        Serial.println("Going DOWN");
    }
    
    

    return input;
}
