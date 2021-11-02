#include "CabButtons.h"
#include "Arduino.h"

CabButtons::CabButtons()
{
    // Red tacile buttons
    for (int i = 22; i < 30; i++)
    {
        pinMode(i, INPUT);
    }

    // Encoder button
    pinMode(2, INPUT);
    
}

CabButtons::~CabButtons()
{
}

int CabButtons::readTactBtn(int buttonNumber)
{
    readInput = digitalRead(22 + buttonNumber);
    return readInput;
}

int CabButtons::readEncBtn()
{
    readInput = digitalRead(2);
    return readInput;
}

void CabButtons::displayBtnInput()
{
      for(int i = 0; i <= 7; i++)
  {
    btnRead[i] = readTactBtn(i);
  }
  btnRead[8] = readEncBtn();

  for(int i = 0; i <= 7; i++)
  {
    Serial.print("Button ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(btnRead[i]);
    Serial.print(", "); 
  }
    Serial.print("Encoder btn ");
    Serial.print(": ");
    Serial.print(btnRead[8]);
    Serial.print(", "); 
  Serial.println("");
}
