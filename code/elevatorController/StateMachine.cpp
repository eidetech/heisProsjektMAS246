#include "StateMachine.h"
#include "CabButtons.h"
#include "Queue.h"
#include "PID.h"
#include "Door.h"
#include "Arduino.h"

CabButtons cabButtons;
PID pidController;
Queue que;
Door doors;

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::idle()
{
    Serial.println("*** STATE: IDLE ***");
    //que.printRequests();

    // Check if any tactile buttons are pressed:
    for (int i = 1; i <= floors; i++)
    {
        if(cabButtons.readTactBtn(i) == 1)
        {
            if (currentFloor > i)
            {
                que.addDown(i);
            }else if(currentFloor < i)
            {
                que.addUp(i);
                Serial.print("Adding up");
                Serial.println(i);
            } 
        }
    }

    // Check if any requests should be completed:
    for (int i = 1; i < floors; i++)
    {
        if(que.upRequests[i-1] == 1 || que.downRequests[i-1] == 1)
        {
            state = PREPARING_MOVE;
        }
    }
    
    
}

void StateMachine::prepareMove()
{
    Serial.println("*** STATE: PREPARE_MOVE ***");
    // Check weight limit etc...

    // After all checks are verified OK, do the correct motion:
    for (int i = 1; i < floors; i++)
    {
        if(que.upRequests[i-1] == 1 && direction == UP)
        {
            anyRequests = true;
            if (currentFloor < i)
            {
                state = MOVING_UP;
                break;
            }else if (currentFloor > i)
            {
                state = MOVING_DOWN;
                break;
            }
        }else if (que.downRequests[i-1] == 1 && direction == DOWN)
        {
            anyRequests = true;
            if (currentFloor < i)
            {
                state = MOVING_UP;
                break;
            }else if (currentFloor > i)
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
        state = IDLE;
    }
    
}


void StateMachine::moveUp()
{
    Serial.println("*** STATE: MOVE_UP ***");
    // Build moveUp function here
    Serial.println("Moving up!");
    //que.printRequests();

    for (int i = currentFloor; i <= floors; i++)
    {
        if (que.upRequests[i] == 1)
        {
            que.printRequests();
            que.removeUp(i);
            que.printRequests();
            currentFloor += i;
            Serial.println("Moving to floor: ");
            Serial.println(currentFloor);

                //1500-(1500-500) = 500 < 1000
            
            int count = 0;
            unsigned long startTime = 0;

            if (count == 0)
            {
                startTime = millis();
            }
            count++;
            

            while((millis() - startTime) <=3000)
            {                
                pidController.PIDCalc(i*2100, 0.1, 0.003, 0, false);
                if ((millis() - startTime) >= 3000)
                {
                    pidController.motorOff();
                    state = ARRIVED;
                }
                
            }
            break;
        }
        
    }
}

void StateMachine::moveDown()
{
    Serial.println("*** STATE: MOVE_DOWN ***");
    // Build moveDown function here
    Serial.println("Moving down!");
}


void StateMachine::arrived()
{
    Serial.println("*** STATE: ARRIVED ***");
    // Build arrived function here
    Serial.println("Arrived!");
    int count = 0;
    unsigned long startTime = 0;

    if (count == 0)
    {
        startTime = millis();
    }
    count++;
            
    while((millis() - startTime) <= 1000)
        {                
            doors.open();
            Serial.println("*** OPENING DOORS ***");
            if ((millis() - startTime) >= 1000)
            {
                delay(5000);
                doors.close();
                Serial.println("*** CLOSING DOORS ***");
                state = PREPARING_MOVE;
                break;
            }
            
        }
}