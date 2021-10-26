
#define ENABLE 7
#define PHASE 6
#define DECAY 5
#define MOTOR_CURRENT A3

#define ENCODER_A 21
#define ENCODER_B 22


void setup() {
  pinMode(ENABLE, OUTPUT);
  pinMode(PHASE, OUTPUT);
  pinMode(DECAY, OUTPUT);

  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_A), ISR_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), ISR_B, CHANGE);

}

void loop() {
  // put your main code here, to run repeatedly:

}
