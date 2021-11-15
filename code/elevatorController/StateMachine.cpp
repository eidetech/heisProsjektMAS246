#include "StateMachine.h"
#include "CabButtons.h"
#include "Queue.h"
#include "PID.h"
#include "Door.h"
#include "Arduino.h"
#include <LiquidCrystal.h>
#include "LED.h"
#include "Overload.h"
#include "Display.h"
//#include "FloorButton.h"
#include "Emergency.h"

// Class objects
CabButtons cabButtons;
PID pidController;
Queue que;
Door doors;
Overload overload;
LED leds;
Display display;
Emergency emergency;
// FloorButton floorButtons;

// Global LiquidCrystal Display
extern LiquidCrystal lcd;

// Constructor
StateMachine::StateMachine()
{
    que.initFloorRequests();
}

// Destructor
StateMachine::~StateMachine()
{
}

void StateMachine::readButtons()
{
    // Check if any tactile buttons are pressed
    for (int i = 1; i <= floors; i++)
    {
        if(cabButtons.readTactBtn(i) == 1)
        {
            // Only buttons that are not on the current floor may be pressed
            if (i != currentFloor)
            {
                que.add(i);
                leds.on(i);
            }
        }
    }
    if (Serial.available() > 0) {
    {
        inData = Serial.read();
        if (inData == 'u')
        {
            Serial.println("Please select the floor you are standing in:");
            delay(3000);
            if (Serial.available() > 0) {
            inData = Serial.read();
            que.addToFloorRequests((inData-48), UP); // -48 because of ASCII characters
            }
        }else if (inData == 'd')
        {
            Serial.println("Please select the floor you are standing in:");
            delay(3000);
            if (Serial.available() > 0) {
            inData = Serial.read();
            que.addToFloorRequests((inData-48), DOWN); // -48 because of ASCII characters
            }
        }
        
        que.printFloorRequests();
    }
    }
    
    
}

void StateMachine::idle()
{
    Serial.println("*** STATE: IDLE ***");

    display.displayDefaultScreen();

    if (direction == UP)
    {
        for (int i = currentFloor; i <= floors; i++)
        {
            if (que.floorRequests[i][1] == 1)
            {
                direction = UP;
                break;
            }
        direction = DOWN;
        }
        
    }else if (direction == DOWN)
    {
        for (int i = currentFloor; i >= 1; i--)
        {
            if (que.floorRequests[i][2])
            {
                direction = DOWN;
                break;
            }
        direction = UP;
        }
    }

    // Check if any floor requests are made from any of the floors (with serial monitor)
    // Check up direction for all floors:
    if (direction == UP)
    {    
        for (int i=0; i<4; i++)
        {
            for (int j = 0; j< 3; j++)
            {
                if (que.floorRequests[i][1])
                {
                    que.add(i+1);
                    leds.on(i+1);
                    que.removeFromFloorRequests(i, UP);
                }
                
            }
        }
    }else if (direction == DOWN)
    {    
        // Check down direction for all floors:
        for (int i=0; i<4; i++)
        {
            for (int j = 0; j< 3; j++)
            {
                if (que.floorRequests[i][2])
                {
                    que.add(i+1);
                    leds.on(i+1);
                    que.removeFromFloorRequests(i, DOWN);
                }
                
            }
        }
    }
    // Check if any requests should be completed:
    for (int i = 1; i <= floors; i++)
    {
        if(que.requests[i-1] == 1)
        {
            state = PREPARING_MOVE;
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
        if (direction == UP)
        {   
            Serial.println("Direction: UP");
        }else if (direction == DOWN)
        {
            Serial.println("Direction: DOWN");
        }else{
            Serial.println("No direction! BAD!");
        }
        
        
        que.printRequests();
        que.printFloorRequests();

        // if (direction == UP)
        // {
        //     for (int i = currentFloor; i <= floors; i++)
        //     {
        //         if (que.requests[i-1] == 1)
        //         {
        //             direction = UP;
        //             break;
        //         }
        //     direction = DOWN;
        //     }
            
        // }else if (direction == DOWN)
        // {
        //     for (int i = currentFloor; i >= 1; i--)
        //     {
        //         if (que.requests[i-1] == 1)
        //         {
        //             direction = DOWN;
        //             break;
        //         }
        //     direction = UP;
        //     }
        // }
        
        for (int i = 1; i <= floors; i++)
        {
            if(que.requests[i-1] == 1 && direction == UP)
            {
                anyRequests = true;
                if (currentFloor <= i)
                {
                    state = MOVING_UP;
                    break;
                }
            }else if (que.requests[i-1] == 1 && direction == DOWN)
            {
                anyRequests = true;
                if (currentFloor >= i)
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
    display.displayMovingUp();

    for (int i = currentFloor; i <= floors; i++)
    {
        
        if (que.requests[i-1] == 1)
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
                // Check for button input
                readButtons();
                // Run DC motor with PID controller
                pidController.PIDCalc((i*encoderPos) - encoderPos, Kp, Ki, Kd, serialPID);
                //Serial.print((millis() - startTime)); Serial.print(" >= "); Serial.println(pidController.runTime * (i-currentFloor));
                if ((millis() - startTime) >= (pidController.runTime * (i-currentFloor)))
                {
                    // Update current floor
                    currentFloor = i;
                    // Display the default screen
                    display.displayDefaultScreen();
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
    display.displayMovingDown();

    for (int i = currentFloor; i >= 1; i--)
    {
        Serial.print("Moving down, i = ");
        Serial.println(i);
        if (que.requests[i-1] == 1)
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
                // Check for button input
                readButtons();
                // Run DC motor with PID controller
                pidController.PIDCalc((i*encoderPos) - encoderPos, 0.1, 0.003, 0, serialPID);
                if ((millis() - startTime) >= (pidController.runTime * abs(currentFloor-i)))
                {
                    // Update current floor
                    currentFloor = i;
                    // Display the default screen
                    display.displayDefaultScreen();
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
        // Check for button input
        readButtons();
        Serial.println("*** OPENING DOORS ***");
        Serial.print("Arrived at floor: ");
        Serial.println(currentFloor);   

        // Open doors
        display.displayOpeningDoors();
        doors.open();
    
        que.remove(currentFloor);

        if ((millis() - startTime) >= doorOpenTime)
        {
            delay(doorOpenTime);
            Serial.println("*** CLOSING DOORS ***");
            // Close doors
            display.displayClosingDoors();
            doors.close();

            // Turn off the stepper motor so it does not draw any current on idle.
            doors.doorDisable();

            // Change to the next state according to the state machine diagram.
            state = PREPARING_MOVE;
            break;
        }
            
    }
}

void StateMachine::emergency()
{
    display.displayEmergency();
    leds.blinkAllLeds();
    pidController.motorOff();
    doors.doorDisable();
}