#include "PID.h"
#include "Arduino.h"

volatile long PID::encoderCount = 0;
float PID::theta_prev = 0;
unsigned long PID::t_prev = 0;
float PID::e_prev = 0;
float PID::int_e_prev = 0;
volatile long PID::globalEncoderCounter = 0;
float PID::u = 0;
float PID::dt = 0;
unsigned long PID::t = 0;
float PID::theta = 0, PID::theta_d = 0;
float PID::e = 0;
float PID::int_e = 0;
int PID::Kp, PID::Ki, PID::Kd;
unsigned long PID::lastMillis = 0;


PID::PID()
{
    pinMode(ENCA, INPUT_PULLUP);
    pinMode(ENCB, INPUT_PULLUP);
    
    attachInterrupt(digitalPinToInterrupt(ENCA), ISR_A, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCB), ISR_B, CHANGE);
}

PID::~PID()
{
}

float PID::PIDcalc()
{ 
  int sampleTime = 10;
  if (checkTime(lastMillis, sampleTime))
  {
  lastMillis = millis();
  int der_e;
  t = millis();
  theta = globalEncoderCounter;
  dt = t-t_prev;
  theta_d = 10;
  e = theta_d - u;

  int_e = int_e + e*dt;
  der_e = (e-e_prev)/dt;

  Kp = 100;
  Ki = 0;
  Kd = 0;

  u = Kp*e + Ki*int_e + Kd*der_e;

  e_prev = e;
  //theta_prev = theta;
  //t_prev = t;

  return u;
  }
}

void PID::ISR_A()
{
  bool pinA = digitalRead(ENCA);
  bool pinB = digitalRead(ENCB);

  if(pinB == LOW)
  {
    if(pinA == HIGH)
    {
      encoderCount++;
    }else
    {
      encoderCount--;
    }
  }else
  {
    if(pinA == HIGH)
    {
      encoderCount++;
      }else
      {
        encoderCount--;
      }
    
  }
  noInterrupts();
  globalEncoderCounter = encoderCount;
  interrupts();
}

void PID::ISR_B()
{
  bool pinA = digitalRead(ENCA);
  bool pinB = digitalRead(ENCB);

  if(pinA == LOW)
  {
    if(pinB == HIGH)
    {
      encoderCount--;
    }else
    {
      encoderCount++;
    }
  }else
  {
    if(pinB == HIGH)
    {
      encoderCount++;
      }else
      {
        encoderCount--;
      }
    
  }
  noInterrupts();
  globalEncoderCounter = encoderCount;
  interrupts();
}

bool PID::checkTime(unsigned long int lastMillisInput, int wait)     
{  
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastMillisInput >= wait)                                // Timer function instead of using delay(), calculates the difference in current milliseconds
  {                                                                           // and previous milliseconds input, then goes "true" when it exceeds wait time input.  
      return true;                                                            // This makes it easy to use timer without blocking the code with a delay().
  }
  return false;
}