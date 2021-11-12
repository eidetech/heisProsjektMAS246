//#include "DCmotor.h"
#include "LED.h"
#include "CabButtons.h"
#include "Door.h"
#include "StateMachine.h"
#include "FloorButton.h"
//#include "PID.h"
#include "Queue.h"
#include "dac.h"
#include <LiquidCrystal.h>
#include "Overload.h"

//DCmotor dcMotor;
LED leds;
//CabButtons cabButtons;
//Door doors;
FloorButton floorButton;
//PID pidController;
StateMachine stateMachine;
Overload overload;

extern LiquidCrystal lcd;

unsigned long lastMillis = 0;
unsigned long currentMillis = 0;

float u;
int dir;

void setup() {
  Serial.begin(9600);
  dac_init();
  set_dac(4095, 4095) ;

  TCCR4B = TCCR4B & 0b11111000 | 0x01; // Setting the PWM frequency from 490Hz to 32kHz
  lcd.begin(16, 2);

// Turn on backlight (PWM 0-255)
  analogWrite(4, 255);
  
}


void loop() {
  //u = pidController.PIDCalc(2100, 2, 0.01, 0.3, true);
  
  switch (stateMachine.state)
  {
  case IDLE:
    stateMachine.idle();
      overload.checkWeigth();
    if(overload.pot > 1400)
    {
      lcd.clear();
      delay(500);
      lcd.print("    ");
      lcd.print(overload.pot);  
      lcd.print(" kg");
      lcd.setCursor(1, 2);
      lcd.print("---Overload---");
      delay(500);
      
    }
    else
    {
      lcd.clear();
      lcd.print("    ");
      lcd.print(overload.pot);  
      lcd.print(" kg");
      }
      
    break;
    
  case PREPARING_MOVE:
    stateMachine.prepareMove();
    
    break;
  case MOVING_UP:
    stateMachine.moveUp();
    break;
  case MOVING_DOWN:
    stateMachine.moveDown();
    break;
  case ARRIVED:
    stateMachine.arrived();
    break;
  // Add more states here...
  default:  
    break;
  }
}
