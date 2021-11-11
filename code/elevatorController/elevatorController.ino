#include "DCmotor.h"
#include "LED.h"
#include "CabButtons.h"
#include "Door.h"
#include "StateMachine.h"
#include "FloorButton.h"
#include "PID.h"
#include <LiquidCrystal.h>
#include "dac.h"


DCmotor dcMotor;
LED leds;
CabButtons cabButtons;
Door doors;
FloorButton floorButton;
PID pidController;


const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long lastMillis = 0;
unsigned long currentMillis = 0;

// elevatorState holds the possible states of the elevator
enum elevatorState {IDLE, REQUEST_UP, REQUEST_DOWN};
elevatorState state = IDLE;

float u;
int dir;

void setup() {
  Serial.begin(115200);
  dac_init();
  set_dac(4095, 4095) ;

  TCCR4B = TCCR4B & 0b11111000 | 0x01; // Setting the PWM frequency from 490Hz to 32kHz
  
  lcd.begin(16, 2);

  // Turn on backlight (PWM 0-255)
  analogWrite(4, 255);

  lcd.print("hallaisikken");
}

void loop() {
  u = pidController.PIDCalc(1200, 4, 0.01, 0.1, true);

  dir = 1;
  if (u<0){
    dir = -1;
  }

  if (u > 255)
  {
    u = 255;
  }
  

  dcMotor.setMotorSpeed(u, dir);

  switch (state)
  {
  case IDLE:
    /* code */
    break;
  case REQUEST_UP:
    /* code */
    break;
  case REQUEST_DOWN:
    /* code */
    break;
  // Add more states here...
  default:  
    break;
  }
}
