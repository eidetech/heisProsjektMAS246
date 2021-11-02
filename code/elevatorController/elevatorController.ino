#include "DCmotor.h"
#include "LED.h"
#include "CabButtons.h"
//#include "LCD.h"
#include <LiquidCrystal.h>

DCmotor dcMotor;
LED leds;
CabButtons cabButtons;

const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  // Turn on backlight (PWM 0-255)
  analogWrite(4, 255);

  lcd.print("hallaisikken");
}

void loop() {
  //dcMotor.setMotorSpeed(25, UP);
  cabButtons.displayBtnInput();

  //leds.on(7);
  
}
