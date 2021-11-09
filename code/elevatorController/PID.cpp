#include "PID.h"
#include "Arduino.h"

#define ENCA 21
#define ENCB 22

volatile int PID::pos_i = 0;
volatile float PID::velocity_i = 0;
volatile long PID::prevT_i = 0;

PID::PID()
{
    pinMode(ENCA,INPUT);
    pinMode(ENCB,INPUT);
    
    attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

PID::~PID()
{
}

float PID::PIDcalc()
{
    // read the position and velocity
    int pos = 0;
    float velocity2 = 0;
    noInterrupts(); // disable interrupts temporarily while reading
    pos = pos_i;
    velocity2 = velocity_i;
    interrupts(); // turn interrupts back on

    // Compute velocity with method 1
    long currT = micros();
    float deltaT = ((float) (currT-prevT))/1.0e6;
    float velocity1 = (pos - posPrev)/deltaT;
    posPrev = pos;
    prevT = currT;

    // Convert count/s to RPM
    float v1 = velocity1/600.0*60.0;
    float v2 = velocity2/600.0*60.0;

    // Low-pass filter (25 Hz cutoff)
    v1Filt = 0.854*v1Filt + 0.0728*v1 + 0.0728*v1Prev;
    v1Prev = v1;
    v2Filt = 0.854*v2Filt + 0.0728*v2 + 0.0728*v2Prev;
    v2Prev = v2;

    // Set a target
    vt = 10;

    // Compute the control signal u
    float kp = 1000;
    float ki = 50;
    float e = vt-v1Filt;
    eintegral = eintegral + e*deltaT;

    float u = kp*e + ki*eintegral;
    return u;
}

static void PID::readEncoder(){
  // Read encoder B when ENCA rises
  int b = digitalRead(ENCB);
  int increment = 0;
  if(b>0){
    // If B is high, increment forward
    increment = 1;
  }
  else{
    // Otherwise, increment backward
    increment = -1;
  }
  pos_i = pos_i + increment;

  // Compute velocity with method 2
  long currT = micros();
  float deltaT = ((float) (currT - prevT_i))/1.0e6;
  velocity_i = increment/deltaT;
  prevT_i = currT;
}