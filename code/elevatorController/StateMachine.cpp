#include "StateMachine.h"
#include "CabButtons.h"
#include "Queue.h"
#include "PID.h"
#include "Door.h"
#include "Arduino.h"
#include <LiquidCrystal.h>
#include "Overload.h"

CabButtons cabButtons;
PID pidController;
Queue que;
Door doors;
Overload overload;

const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
    
StateMachine::StateMachine()
{

}

StateMachine::~StateMachine()
{
}

void StateMachine::idle()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("Heis(ann)! v0.1");
    lcd.setCursor(4,2);
    lcd.print(currentFloor);
    lcd.print(".");
    lcd.print(" floor");

    Serial.println("*** STATE: IDLE ***");
    if(overload.checkWeight())
    {
    lcd.clear();
    lcd.print("Heis(ann)! v0.1");
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
    Serial.println("*** STATE: PREPARE_MOVE ***");
    // Checking weigth
   

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
    

    // After all checks are verified OK, do the correct motion:
    for (int i = 1; i <= floors; i++)
    {
        if(que.upRequests[i-1] == 1 && direction == UP)
        {
            anyRequests = true;
            if (currentFloor < i)
            {
                state = MOVING_UP;
                break;
            //}else if (currentFloor > i)
            //{
            //    state = MOVING_DOWN;
            //    break;
            }
        }else if (que.downRequests[i-1] == 1 && direction == DOWN)
        {
            anyRequests = true;
            if (currentFloor > i)
            {
                state = MOVING_DOWN;
                break;
            // }else if (currentFloor > i)
            // {
            //     state = MOVING_DOWN;
            //     break;
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
    Serial.println("*** STATE: MOVING_UP ***");

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
    Serial.println("*** STATE: MOVING_DOWN ***");

    for (int i = 1; i <= floors; i++)
    {
        if (que.downRequests[i-1] == 1)
        {
            que.printRequests();
            que.removeDown(i-1);
            que.printRequests();
            currentFloor -= i;
            Serial.println("Moving to floor: ");
            Serial.println(currentFloor);
            
            int count = 0;
            unsigned long startTime = 0;

            if (count == 0)
            {
                startTime = millis();
            }
            count++;
            

            while((millis() - startTime) <= pidController.runTime * (currentFloor-(i-1)))
            {                
                pidController.PIDCalc(-(currentFloor-i)*2100, 0.1, 0.003, 0, false);
                if ((millis() - startTime) >= pidController.runTime * (currentFloor-(i-1)))
                {
                    pidController.motorOff();
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
            
    while((millis() - startTime) <= 1000)
        {             
            Serial.println("*** OPENING DOORS ***");
            Serial.println(currentFloor);   
            doors.open();
            if ((millis() - startTime) >= 1000)
            {
                delay(doors.doorOpeningTime);
                Serial.println("*** CLOSING DOORS ***");
                doors.close();
                doors.doorDisable();
                state = PREPARING_MOVE;
                break;
            }
            
        }
}
