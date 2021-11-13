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

int Queue::addUp(int floorNum)
{
    upRequests[floorNum-1] = 1;
    Serial.print("Floor num:");
    Serial.println(floorNum);
}

int Queue::addDown(int floorNum)
{
    downRequests[floorNum-1] = 1;
}

int Queue::removeUp(int floorNum)
{
    upRequests[floorNum-1] = 0;
}

int Queue::removeDown(int floorNum)
{
    downRequests[floorNum-1] = 0;
}

void Queue::printRequests()
{
    Serial.println("Up requests: ");
    for (int i = 1; i <= floors; i++)
    {
        Serial.print(upRequests[i-1]);
    }
    Serial.println(" ");
    Serial.println("Down requests: ");
    for (int i = 1; i <= floors; i++)
    {
        Serial.print(downRequests[i-1]);
    }
    Serial.println(" ");
}

void Queue::printRequests2()
{
    Serial.println("Requests: (in add/remove system)");
    for (int i = 1; i <= floors; i++)
    {
        Serial.print(requests[i-1]);
    }
    Serial.println(" ");
}