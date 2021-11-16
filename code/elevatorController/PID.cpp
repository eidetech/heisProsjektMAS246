#include "PID.h"
#include "DCmotor.h"
#include "Arduino.h"

// safePos must be defined as volatile, so that the ISR can control that variable.
static volatile float safePos = 0; // Note on volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
static unsigned long t_prev = 0;
static float e_prev = 0;
static float e;
static float e_integral = 0;
static float e_derivative = 0;
static float activateIntegral = 10;
static int motorDirection = 1;
static float PID::pos = 0; 

DCmotor dcMotor;

PID::PID()
{
// Interrupt setup
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder_ISR, RISING);
}

PID::~PID()
{
}

float PID::PIDCalc(float setPoint, float Kp, float Ki, float Kd, bool serialPlot)
{ 
  //setPoint = 1000*sin(t_prev/1e6);
  unsigned long t = micros();
  float dt = (t - t_prev)/(1.0e6); // Convert to s
  t_prev = t;

  // Read the safePos
  pos = 0; 
  noInterrupts(); // Disable interrupts
  pos = safePos;
  interrupts(); // Enable interrupts
  
  // Calculate errors
  e = setPoint - pos;

  // Integral
  e_integral = e_integral + e*dt;

  // Derivative
  e_derivative = (e-e_prev)/(dt);

  // Serial.println("e & e_integral & e_derivative");
  // Serial.print(e);
  // Serial.print(" = ");
  // Serial.print(e_integral);
  //  Serial.print(" = ");
  // Serial.print(e_derivative);

  // if (e == 0)
  // {
  //   e_derivative = 0;
  // }
  
  // Calculate control signal u
  float u = Kp*e + Ki*e_integral + Kd*e_derivative;

  // Set motor output limits
  float pwr = fabs(u);

  if( pwr > 50 ){
    pwr = 50;
  }

  // motor direction
  int dir = LOW;
  if(u>0){
    dir = HIGH;
  }

  if(pos < setPoint)
  {
    dcMotor.setMotorSpeed(pwr, dir);
  }else if(pos > setPoint)
  {
    dcMotor.setMotorSpeed(pwr, dir);
  }

  e_prev = e;

  if(serialPlot)
  {
  // Serial plotting
  Serial.print(setPoint);
  Serial.print(" ");
  Serial.print(pos);
  Serial.println();
  }
  return u;
}

void PID::motorOff()
{
  dcMotor.motorOff();
}

// readEncoder ISR
void PID::readEncoder_ISR(){
  int b = digitalRead(ENCB);
  if(b > 0){
    safePos++;
  }
  else{
    safePos--;
  }
}
