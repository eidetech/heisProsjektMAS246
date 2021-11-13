#include "Display.h"
#include <LiquidCrystal.h>
#include "StateMachine.h"
#include "Arduino.h"
	
Display::Display()
{
	
}
	
Display::~Display()
{
	
}

extern StateMachine stateMachine;

// LCD display
const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void Display::displayDefaultScreen()
{
    // Print default screen
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("Vertical Express");
    lcd.setCursor(4,2);
    lcd.print(stateMachine.currentFloor);
    lcd.print(".");
    lcd.print(" floor");
}

void Display::displayMovingUp()
{
    // Display graphics for moving up
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(char(1));
    lcd.setCursor(0, 0);
    lcd.print(char(2));

    lcd.setCursor(15, 1);
    lcd.print(char(1));
    lcd.setCursor(15, 0);
    lcd.print(char(2));

    lcd.setCursor(4, 0);
    lcd.print("Elevator");
    lcd.setCursor(4, 1);
    lcd.print("Moving up");
}

void Display::displayMovingDown()
{
    // Display graphics for moving down
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(char(3));
    lcd.setCursor(0, 0);
    lcd.print(char(1));

    lcd.setCursor(15, 1);
    lcd.print(char(3));
    lcd.setCursor(15, 0);
    lcd.print(char(1));

    lcd.setCursor(4, 0);
    lcd.print("Elevator");
    lcd.setCursor(2, 1);
    lcd.print("Moving Down");
}

void Display::displayOpeningDoors()
{
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Opening Doors");
    lcd.setCursor(2, 1);
    lcd.print(char(4));
    lcd.print(char(6));
    lcd.setCursor(13, 1);
    lcd.print(char(6));
    lcd.print(char(5));
}

void Display::displayClosingDoors()
{
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Closing Doors");
    lcd.setCursor(2, 1);
    lcd.print(char(6));
    lcd.print(char(5));
    lcd.setCursor(13, 1);
    lcd.print(char(4));
    lcd.print(char(6));
}

void Display::clearDisplay()
{
    lcd.clear();
}