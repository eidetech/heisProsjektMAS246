#define ENCA 20
#define ENCB 21
#define ENABLE 7
#define PHASE 6
#define DECAY 5

// safePos must be defined as volatile, so that the ISR can control that variable.
volatile int safePos = 0; // Note on volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
unsigned long t_prev = 0;
float e_prev = 0;
float e;
float e_integral = 0;
float e_derivative = 0;

int runTime = 1000;
int waitTime = 10000;

void setup() {
  Serial.begin(115200);

  // Interrupt setup
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);

  // Motor pins setup
  pinMode(ENABLE, OUTPUT);
  pinMode(PHASE, OUTPUT);
  pinMode(DECAY, OUTPUT);
}

void loop() {

  int count = 0;
  unsigned long startTime = 0;

  if (count == 0)
  {
      startTime = millis();
  }
  count++;
  while((millis() - startTime) <= runTime)
  {
  // Example on setpoints:
  int setpoint = 1200;
  //int setpoint = 1000*sin(t_prev/1e6);

  // PID constants
  float Kp = 1;
  float Ki = 0;
  float Kd = 0;
 
  unsigned long t = micros();
  float dt = (t - t_prev)/(1.0e6); // Convert to s
  t_prev = t;

  // Read the safePos
  int pos = 0; 
  noInterrupts(); // Disable interrupts
  pos = safePos;
  interrupts(); // Enable interrupts
  
  // Calculate errors
  e = setpoint - pos;

  // Integral
  e_integral = e_integral + e*dt;

  // Derivative
  e_derivative = (e-e_prev)/(dt);

  // Calculate control signal u
  float u = Kp*e + Ki*e_integral + Kd*e_derivative;

  // Set motor output limits
  float pwr = fabs(u);
  if( pwr > 255 ){
    pwr = 255;
  }

  // motor direction
  int dir = LOW;
  if(u>0){
    dir = HIGH;
  }

  if(pos < setpoint)
  {
  // Motor control
  digitalWrite(DECAY, LOW); 
  digitalWrite(PHASE, HIGH);
  analogWrite(ENABLE, pwr);
  }else if(pos > setpoint)
  {
  digitalWrite(DECAY, LOW); 
  digitalWrite(PHASE, LOW);
  analogWrite(ENABLE, pwr);
  }

  e_prev = e;

  // Serial plotting
  Serial.print("Setpoint:");
  Serial.print(setpoint);
  Serial.print(",");
  Serial.print("Position:");
  Serial.println(pos);
  
  if ((millis() - startTime) >= runTime)
  {
    safePos = 0; // Note on volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
    pos = 0;
    t_prev = 0;
    e_prev = 0;
    e = 0;
    e_integral = 0;
    e_derivative = 0;
    digitalWrite(DECAY, HIGH); 
    digitalWrite(PHASE, HIGH);
    analogWrite(ENABLE, 0);
    delay(waitTime);
    break;
  }
}
}

// readEncoder ISR
void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    safePos++;
  }
  else{
    safePos--;
  }
}
