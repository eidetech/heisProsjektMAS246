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
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    floorRequest = Serial.read();
    delay(100);
    Serial.print("Read from the serial input:");
    Serial.println(floorRequest-48);
  }
    return floorRequest-48;
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
