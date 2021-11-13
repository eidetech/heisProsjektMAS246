#include "Queue.h"
#include "Arduino.h"

Queue::Queue()
{
}

Queue::~Queue()
{
}

int Queue::add(int floorNum)
{
    requests[floorNum-1] = 1;
}

int Queue::remove(int floorNum)
{
    requests[floorNum-1] = 0;
}

void Queue::printRequests()
{
    Serial.println("Requests: (in add/remove system)");
    for (int i = 1; i <= floors; i++)
    {
        Serial.print(requests[i-1]);
    }
    Serial.println(" ");
}

void Queue::initFloorRequests()
{
    for (int i=0; i<4; i++)
    {
        floorRequests[i][0] = i;
        for (int j = 0; j< 3; j++)
            {
            floorRequests[i][1] = 0;
            floorRequests[i][2] = 0;
            Serial.print(floorRequests[i][j]);
            Serial.print("\t");
            }
            Serial.println();
    }
}

void Queue::printFloorRequests()
{
    Serial.print("Floor");
    Serial.print("\t");
    Serial.print("UP");
    Serial.print("\t");
    Serial.println("DOWN");


    for (int i=0; i<4; i++)
    {
        for (int j = 0; j< 3; j++)
            {
            Serial.print(floorRequests[i][j]);
            Serial.print("\t");
            }
            Serial.println();
    }
}

void Queue::addToFloorRequests(int floor, elevatorDirection dir)
{   int j = 0;
    if (dir == UP)
    {
        j = 1;
    }else if (dir == DOWN)
    {
        j = 2;
    }
    floorRequests[floor-1][j] = 1;
}

void Queue::removeFromFloorRequests(int floor, elevatorDirection dir)
{
    int j = 0;
    if (dir == UP)
    {
        j = 1;
    }else if (dir == DOWN)
    {
        j = 2;
    }
    floorRequests[floor][j] = 0;
}