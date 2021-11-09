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
  t = millis();
  theta = globalEncoderCounter;
  dt = t-t_prev;
  theta_d = 10;
  e = theta-theta_d;

  int_e = int_e_prev + (dt*(e+e_prev)/2);

  Kp = 1;
  Ki = 0;
  Kd = 0;

  u = Kp*e + Ki * int_e + (Kd * (e-e_prev)/dt);

  theta_prev = theta;
  t_prev = t;

  return u;
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