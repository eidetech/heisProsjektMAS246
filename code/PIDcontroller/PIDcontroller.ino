#define ENCA 20
#define ENCB 21
#define ENABLE 7
#define PHASE 6
#define DECAY 5

volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  
  pinMode(ENABLE, OUTPUT);
  pinMode(PHASE, OUTPUT);
  pinMode(DECAY, OUTPUT);
  
  Serial.println("target pos");
}

void loop() {
  // set target position
  //int target = 1200;
  int target = 1000*sin(prevT/1e6);

  // PID constants
  float kp = 4;
  float ki = 0.01;
  float kd = 0.1;
  

  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;

  // Read the position
  int pos = 0; 
  noInterrupts(); // disable interrupts temporarily while reading
  pos = posi;
  interrupts(); // turn interrupts back on
  
  // error
  int e = pos - target;

  // derivative
  float dedt = (e-eprev)/(deltaT);

  // integral
  eintegral = eintegral + e*deltaT;

  // control signal
  float u = kp*e + kd*dedt + ki*eintegral;

  // motor power
  float pwr = fabs(u);
  if( pwr > 255 ){
    pwr = 255;
  }

  // motor direction
  int dir = LOW;
  if(u<0){
    dir = HIGH;
  }

  if(pos < target)
  {
  // signal the motor
  digitalWrite(DECAY, LOW); 
  digitalWrite(PHASE, HIGH);
  analogWrite(ENABLE, pwr);
  }else if(pos > target)
  {
  digitalWrite(DECAY, LOW); 
  digitalWrite(PHASE, LOW);
  analogWrite(ENABLE, pwr);
  }

  // store previous error
  eprev = e;

  Serial.print(target);
  Serial.print(" ");
  Serial.print(pos);
  Serial.println();
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}
