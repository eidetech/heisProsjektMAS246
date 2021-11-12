#include "DCmotor.h"
#include "LED.h"
#include "CabButtons.h"
#include "Door.h"
#include "StateMachine.h"
#include "FloorButton.h"
#include "PID.h"
#include "Que.h"
#include "Overload.h"
#include <LiquidCrystal.h>
#include "dac.h"


DCmotor dcMotor;
LED leds;
//CabButtons cabButtons;
Door doors;
FloorButton floorButton;
PID pidController;
StateMachine stateMachine;
Overload overload;

const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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
  //u = pidController.PIDCalc(10*2100, 2, 0.01, 0.3, true);

  
  switch (stateMachine.state)
  {
  case IDLE:
    stateMachine.idle();
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
  // Add more states here...
  default:  
    break;
  }
  delay(500);
}
