#include "Overload.h"
#include "Arduino.h"

Overload::Overload()
{ 
  // Potmeter
    pinMode(A0, INPUT);   
}

Overload::~Overload()
  {
  }

// Read poteniometer and store data

int Overload::checkWeigth()
{
     pot = analogRead(A0);
    
    if (pot > 500)
  {
    Serial.println("ALARM");
    lcd.print("hallaisikken");
  }
    return;
}