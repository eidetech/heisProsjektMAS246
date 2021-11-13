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