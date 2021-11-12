#include "Que.h"
#include "Arduino.h"

Que::Que()
{
}

Que::~Que()
{
}

int Que::addUp(int floorNum)
{
    upRequests[floorNum-1] = 1;
    Serial.print("Floor num:");
    Serial.println(floorNum);
}

int Que::addDown(int floorNum)
{
    downRequests[floorNum-1] = 1;
}

int Que::removeUp(int floorNum)
{
    upRequests[floorNum-1] = 0;
}

int Que::removeDown(int floorNum)
{
    downRequests[floorNum-1] = 0;
}

void Que::printRequests()
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