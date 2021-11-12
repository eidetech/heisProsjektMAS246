#include "StateMachine.h"
#include "CabButtons.h"
#include "Que.h"
#include "Arduino.h"

CabButtons cabButtons;
Que que;

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::idle()
{
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
    // Check weight limit etc...
    Serial.println("Preparing to move!");
}

void StateMachine::moveUp()
{
    // Build moveUp function here
}

void StateMachine::moveDown()
{
    // Build moveDown function here
}