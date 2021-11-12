#include "StateMachine.h"
#include "CabButtons.h"
#include "Queue.h"
#include "PID.h"
#include "Door.h"
#include "Arduino.h"
#include <LiquidCrystal.h>
#include "LED.h"
#include "Overload.h"

// Class objects
CabButtons cabButtons;
PID pidController;
Queue que;
Door doors;
Overload overload;
LED leds;

// LCD display
const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
    
// Constructor
StateMachine::StateMachine()
{
}

// Destructor
StateMachine::~StateMachine()
{
}

void StateMachine::readButtons()
{
    // Check if any tactile buttons are pressed:
    for (int i = 1; i <= floors; i++)
    {
        if(cabButtons.readTactBtn(i) == 1)
        {
            if (currentFloor > i)
            {
                que.addDown(i);
                leds.on(i);
                Serial.print("Adding down");
                Serial.println(i);
            }else if(currentFloor < i)
            {
                que.addUp(i);
                leds.on(i);
                Serial.print("Adding up");
                Serial.println(i);
            } 
        }
    }
}

void StateMachine::idle()
{
    Serial.println("*** STATE: IDLE ***");
    if(overload.checkWeight()) // Returns true if no overload
    {
        // If no overload, then continue
        displayDefaultScreen();

        // Check if any requests should be completed:
        for (int i = 1; i <= floors; i++)
        {
            if(que.upRequests[i-1] == 1 || que.downRequests[i-1] == 1)
            {
                state = PREPARING_MOVE;
            }
        }
    }
}

void StateMachine::prepareMove()
{
    // Checking overload
    if(overload.checkWeight())
    {
        // If no overload, then continue
        Serial.println("*** STATE: PREPARE_MOVE ***");
        que.printRequests();

        for (int i = 1; i <= floors; i++)
        {
            if(que.upRequests[i-1] == 1)
            {
                direction = UP;
                break;
            }else if (que.downRequests[i-1] == 1)
            {
                direction = DOWN;
                break;
            }
            
        }
        
        for (int i = 1; i <= floors; i++)
        {
            if(que.upRequests[i-1] == 1 && direction == UP)
            {
                anyRequests = true;
                if (currentFloor < i)
                {
                    state = MOVING_UP;
                    break;
                }
            }else if (que.downRequests[i-1] == 1 && direction == DOWN)
            {
                anyRequests = true;
                if (currentFloor > i)
                {
                    state = MOVING_DOWN;
                    break;
                }
                
            }else
            {
                anyRequests = false;
            }
        }
        if (!anyRequests)
        {
            Serial.println("No requests, going back to IDLE state.");
            state = IDLE;
        }
    }

}

void StateMachine::moveUp()
{
    Serial.println("*** STATE: MOVING_UP ***");
    // Display moving up graphics on LCD display
    displayMovingUp();

    for (int i = 1; i <= floors; i++)
    {
        if (que.upRequests[i-1] == 1)
        {
            int count = 0;
            unsigned long startTime = 0;

            if (count == 0)
            {
                startTime = millis();
            }
            count++;
            
            while((millis() - startTime) <= (pidController.runTime * (i-currentFloor)))
            {   
                // Run DC motor with PID controller
                pidController.PIDCalc((i*encoderPos) - encoderPos, Kp, Ki, Kd, false);
                if ((millis() - startTime) >= (pidController.runTime * (i-currentFloor)))
                {
                    // Update current floor
                    currentFloor = i;
                    // Display the default screen
                    displayDefaultScreen();
                    // Turn off LED light corresponding to floor
                    leds.off(i);
                    // Make sure the motor is fully off
                    pidController.motorOff();
                    // Change state to arrived, so that the next switch state in elevatorController.ino will be ARRIVED
                    state = ARRIVED;
                }
                
            }
            break;
        }
        
    }
}

void StateMachine::moveDown()
{
    Serial.println("*** STATE: MOVING_DOWN ***");
    // Display moving down graphics on LCD display
    displayMovingDown();

    for (int i = 1; i <= floors; i++)
    {
        if (que.downRequests[i-1] == 1)
        {
            int count = 0;
            unsigned long startTime = 0;

            if (count == 0)
            {
                startTime = millis();
            }
            count++;

            while((millis() - startTime) <= (pidController.runTime * abs(currentFloor-i)))
            {   
                // Run DC motor with PID controller
                pidController.PIDCalc((i*encoderPos) - encoderPos, 0.1, 0.003, 0, false);
                if ((millis() - startTime) >= (pidController.runTime * abs(currentFloor-i)))
                {
                    // Update current floor
                    currentFloor = i;
                    // Display the default screen
                    displayDefaultScreen();
                    // Turn off LED light corresponding to floor
                    leds.off(i);
                    // Make sure the motor is fully off
                    pidController.motorOff();
                    // Change state to arrived, so that the next switch state in elevatorController.ino will be ARRIVED
                    state = ARRIVED;
                }
                
            }
            break;
        }
        
    }
}

void StateMachine::arrived()
{
    Serial.println("*** STATE: ARRIVED ***");
    int count = 0;
    unsigned long startTime = 0;

    if (count == 0)
    {
        startTime = millis();
    }
    count++;
            
    while((millis() - startTime) <= doorOpenTime)
    {             
        Serial.println("*** OPENING DOORS ***");
        Serial.print("Arrived at floor: ");
        Serial.println(currentFloor);   

        // Open doors
        doors.open();
    
        if (direction == UP)
        {
            que.printRequests();
            que.removeUp(currentFloor);
            que.printRequests();
        }else if (direction == DOWN)
        {
            que.printRequests();
            que.removeDown(currentFloor);
            que.printRequests();
        }

        if ((millis() - startTime) >= doorOpenTime)
        {
            delay(doorOpenTime);
            Serial.println("*** CLOSING DOORS ***");
            // Close doors
            doors.close();

            // Turn off the stepper motor so it does not draw any current on idle.
            doors.doorDisable();

            // Change to the next state according to the state machine diagram.
            state = PREPARING_MOVE;
            break;
        }
            
    }
}

void StateMachine::displayDefaultScreen()
{
    // Print default screen
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("Vertical Express");
    lcd.setCursor(4,2);
    lcd.print(currentFloor);
    lcd.print(".");
    lcd.print(" floor");
}

void StateMachine::displayMovingUp()
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

void StateMachine::displayMovingDown()
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
    lcd.print("Moving down");
}

void StateMachine::createSpecialChars()
{
    // Define and store the special characters
    byte line[8]={B00100,B00100,B00100,B00100,B00100,B00100,B00100,B00100,};
    byte upArrow[8]={B00100,B01110,B11111,B00100,B00100,B00100,B00100,B00100,};
    byte downArrow[8]={B00100,B00100,B00100,B00100,B00100,B11111,B01110,B00100,};
    lcd.createChar(1, line);
    lcd.createChar(2 , upArrow);
    lcd.createChar(3 , downArrow);
}
