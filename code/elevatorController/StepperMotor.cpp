#include "StepperMotor.h"
#include "Arduino.h"

StepperMotor::StepperMotor()
{
    pinMode(EnableA, OUTPUT);
    pinMode(EnableB, OUTPUT);
    pinMode(PhaseA, OUTPUT);
    pinMode(PhaseB, OUTPUT);

    pinMode(SDI_pin, OUTPUT);
    pinMode(SCK_pin, OUTPUT);
    pinMode(CS_pin, OUTPUT);
    pinMode(LDAC_pin, OUTPUT);
}

StepperMotor::~StepperMotor()
{
}

void StepperMotor::moveForward(int steps) 
{

    while(stepCount < steps)
    {
        currentMillis = millis();
        if((currentMillis-lastMillis) > steppingDelay && stepSequence == 1)
        {
            digitalWrite (EnableA, HIGH);     // Step 1                       // Here are the 8 halfsteps that are cariied out one by one and looped until it has reached wanted number of loops
            digitalWrite (EnableB, HIGH);                                     // Using the stepsequence variable to keep track of what step to execute when
            digitalWrite (PhaseA, LOW);
            digitalWrite (PhaseB, LOW);
            lastMillis = millis();
            stepSequence = 2;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 2)
        {
            digitalWrite (EnableA, LOW);      // Step 2
            digitalWrite (EnableB, HIGH);
            digitalWrite (PhaseA, LOW);
            digitalWrite (PhaseB, LOW);
            lastMillis = millis();
            stepSequence = 3;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 3)
        {
            digitalWrite (EnableA, HIGH);      // Step 3
            digitalWrite (EnableB, HIGH);
            digitalWrite (PhaseA, HIGH);
            digitalWrite (PhaseB, LOW);
            lastMillis = millis();
            stepSequence = 4;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 4)
        {
            digitalWrite (EnableA, HIGH);      // Step 4
            digitalWrite (EnableB, LOW);
            digitalWrite (PhaseA, HIGH);
            digitalWrite (PhaseB, LOW);
            lastMillis = millis();
            stepSequence = 5;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 5)
        {
            digitalWrite (EnableA, HIGH);      // Step 5
            digitalWrite (EnableB, HIGH);
            digitalWrite (PhaseA, HIGH);
            digitalWrite (PhaseB, HIGH);
            lastMillis = millis();
            stepSequence = 6;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 6)
        {
            digitalWrite (EnableA, LOW);      // Step 6
            digitalWrite (EnableB, HIGH);
            digitalWrite (PhaseA, LOW);
            digitalWrite (PhaseB, HIGH);
            lastMillis = millis();
            stepSequence = 7;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 7)
        {
            digitalWrite (EnableA, HIGH);      // Step 7
            digitalWrite (EnableB, HIGH);
            digitalWrite (PhaseA, LOW);
            digitalWrite (PhaseB, HIGH);
            lastMillis = millis();
            stepSequence = 8;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 8)
        {
            digitalWrite (EnableA, HIGH);      // Step 8
            digitalWrite (EnableB, LOW);
            digitalWrite (PhaseA, LOW);
            digitalWrite (PhaseB, LOW);
            lastMillis = millis();
            stepSequence = 1;
            stepCount++;
        }
    
    }
    if(stepCount == steps)
    {
      stepSequence = 1;
    }
}


void StepperMotor::moveBackward(int steps) 
{

    while(stepCount < steps)
    {
        currentMillis = millis();
        if((currentMillis-lastMillis) > steppingDelay && stepSequence == 8)
        {
            digitalWrite (EnableA, HIGH);     // Step 1                       // Here are the 8 halfsteps that are cariied out one by one and looped until it has reached wanted number of loops
            digitalWrite (EnableB, HIGH);                                     // Using the stepsequence variable to keep track of what step to execute when
            digitalWrite (PhaseA, LOW);
            digitalWrite (PhaseB, LOW);
            lastMillis = millis();
            stepSequence = 1;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 7)
        {
            digitalWrite (EnableA, LOW);      // Step 2
            digitalWrite (EnableB, HIGH);
            digitalWrite (PhaseA, LOW);
            digitalWrite (PhaseB, LOW);
            lastMillis = millis();
            stepSequence = 8;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 6)
        {
            digitalWrite (EnableA, HIGH);      // Step 3
            digitalWrite (EnableB, HIGH);
            digitalWrite (PhaseA, HIGH);
            digitalWrite (PhaseB, LOW);
            lastMillis = millis();
            stepSequence = 7;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 5)
        {
            digitalWrite (EnableA, HIGH);      // Step 4
            digitalWrite (EnableB, LOW);
            digitalWrite (PhaseA, HIGH);
            digitalWrite (PhaseB, LOW);
            lastMillis = millis();
            stepSequence = 6;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 4)
        {
            digitalWrite (EnableA, HIGH);      // Step 5
            digitalWrite (EnableB, HIGH);
            digitalWrite (PhaseA, HIGH);
            digitalWrite (PhaseB, HIGH);
            lastMillis = millis();
            stepSequence = 5;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 3)
        {
            digitalWrite (EnableA, LOW);      // Step 6
            digitalWrite (EnableB, HIGH);
            digitalWrite (PhaseA, LOW);
            digitalWrite (PhaseB, HIGH);
            lastMillis = millis();
            stepSequence = 4;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 2)
        {
            digitalWrite (EnableA, HIGH);      // Step 7
            digitalWrite (EnableB, HIGH);
            digitalWrite (PhaseA, LOW);
            digitalWrite (PhaseB, HIGH);
            lastMillis = millis();
            stepSequence = 3;
            stepCount++;
        }else if((currentMillis-lastMillis) > steppingDelay && stepSequence == 1)
        {
            digitalWrite (EnableA, HIGH);      // Step 8
            digitalWrite (EnableB, LOW);
            digitalWrite (PhaseA, LOW);
            digitalWrite (PhaseB, LOW);
            lastMillis = millis();
            stepSequence = 2;
            stepCount++;
        }
        Serial.print("Step count: ");
        Serial.println(stepCount);
    
    }
    if(stepCount == steps)
    {
      stepSequence = 1;
      Serial.print("stepSequence: ");
      Serial.println(stepSequence);
      stepCount = 0;
    }

}
