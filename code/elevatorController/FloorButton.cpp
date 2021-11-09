#include "FloorButton.h"
#include "Arduino.h"

FloorButton::FloorButton()
{    
}

FloorButton::~FloorButton()
{
}

int FloorButton::readFloorBtn()
{
  Serial.print("Please select floor.");
  floorRequest = Serial.read();
  Serial.println(floorRequest);
  return floorRequest;
}

int FloorButton::readUpDown()
{
  Serial.print("Please select direction (u/d).");
  input = Serial.read();
    if (input == 'u')
    {
        Serial.println("Going UP");
    }
    else if (input == 'd')
    {
        Serial.println("Going DOWN");
    }
    
    return input;
}
