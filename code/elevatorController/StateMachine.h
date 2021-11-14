#pragma once

// elevatorState holds the possible states of the elevator
enum elevatorState {IDLE, PREPARING_MOVE, MOVING_UP, MOVING_DOWN, ARRIVED, EMERGENCY};
enum elevatorDirection {UP, DOWN};

class StateMachine
{
private:
    
public:
    StateMachine();
    ~StateMachine();

    void readButtons();
    
    // States
    void idle();
    void prepareMove();
    void moveUp();
    void moveDown();
    void arrived();
    void emergency();

    int floors = 4;
    int encoderPos = 2100;
    int doorOpenTime = 1000;
    // float Kp = 0.1;
    // float Ki = 0.003;
    // float Kd = 0;
    float Kp = 1.2;
    float Ki = 0.005;
    float Kd = 0.06;
    bool serialPID = true;

    int currentFloor = 1;
    bool anyRequests = false;
    

    int inData = 0;

    elevatorState state = IDLE;
    elevatorDirection direction = UP;
};