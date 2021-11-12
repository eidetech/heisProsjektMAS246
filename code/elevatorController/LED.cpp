#include "LED.h"
#include "Arduino.h"

// Constructor
LED::LED()
{
    for (int i = 42; i < 50; i++)
    {
        pinMode(i, OUTPUT);
    }
    
}

// Destructor
LED::~LED()
{
}

// Turn on all led's in sequence
void LED::lightUpSeq()
{
    for (int i = 42; i < 50; i++)
    {
       digitalWrite(i, HIGH);
       delay(200);
    }

        for (int i = 49; i > 41; i--)
    {
       digitalWrite(i, LOW);
       delay(200);
    }
    
}

// Turn on specific LED
void LED::on(int led)
{
    digitalWrite(49-led, HIGH);
}

// Turn off specific LED
void LED::off(int led)
{
    digitalWrite(49-led, LOW);
}
