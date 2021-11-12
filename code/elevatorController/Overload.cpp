#include "Overload.h"
#include "Arduino.h"
#include "LiquidCrystal.h"

extern LiquidCrystal lcd;

Overload::Overload()
{ 
  // Potmeter
  pinMode(A0, INPUT);   
}

Overload::~Overload()
  {
  }

// Read poteniometer and store data

bool Overload::checkWeight()
{
  pot = analogRead(A0)*2;
  if(pot > 1400)
  {
    lcd.clear();
    delay(500);
    lcd.print("    ");
    lcd.print(pot); 
    lcd.print(" kg");
    lcd.setCursor(1, 2);
    lcd.print("---Overload---");
    delay(500);
    return false;
  }
  return true;
}
