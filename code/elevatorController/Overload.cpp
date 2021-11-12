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
     pot = analogRead(A0)*2;
      
      Serial.print(pot);
      Serial.println("kg");
      Serial.println("OK");
      
      if (pot > 1500)
      {
        Serial.println("ALARM");
        
      }
}
