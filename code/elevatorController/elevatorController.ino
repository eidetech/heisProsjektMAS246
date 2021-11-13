#include "CabButtons.h"
#include "Door.h"
#include "StateMachine.h"
#include "FloorButton.h"
#include "Queue.h"
#include "dac.h"
#include <LiquidCrystal.h>

// Class objects
FloorButton floorButton;
StateMachine stateMachine;

// Global LiquidCrystal Display
extern LiquidCrystal lcd;

// Store time variables and set the update rate
unsigned long lastMillis = 0;
unsigned long currentMillis = 0;
const int updateRate = 100; // ms

void setup() {
  Serial.begin(9600);
  dac_init();
  set_dac(4095, 4095) ;

  TCCR4B = TCCR4B & 0b11111000 | 0x01; // Setting the PWM frequency from 490Hz to 32kHz
  lcd.begin(16, 2);

  // Define and store the special characters
    byte empty[8]={B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000,};
    byte line[8]={B00100,B00100,B00100,B00100,B00100,B00100,B00100,B00100,};
    byte upArrow[8]={B00100,B01110,B11111,B00100,B00100,B00100,B00100,B00100,};
    byte downArrow[8]={B00100,B00100,B00100,B00100,B00100,B11111,B01110,B00100,};
    byte leftArrow[8]={B00010,B00110,B01110,B11111,B11111,B01110,B00110,B00010,};
    byte rightArrow[8]={B01000,B01100,B01110,B11111,B11111,B01110,B01100,B01000,};
    byte horizontalLine[8]={B00000,B00000,B00000,B11111,B11111,B00000,B00000,B00000,};
    lcd.createChar(1, line);
    lcd.createChar(2 , upArrow);
    lcd.createChar(3 , downArrow);
    lcd.createChar(4 , leftArrow);
    lcd.createChar(5 , rightArrow);
    lcd.createChar(6 , horizontalLine);

// Turn on backlight on LCD (PWM 0-255)
  analogWrite(4, 255);
}

void loop() {
  // Capture current time in ms
  currentMillis = millis();

  // Read buttons
  stateMachine.readButtons();

  // Update system if the update rate has passed
  if(currentMillis - lastMillis >= updateRate)
  {
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
    case ARRIVED:
      stateMachine.arrived();
      break;
    default:  
      break;
    }
  // Update lastMillis
  lastMillis = millis();
  }
}
