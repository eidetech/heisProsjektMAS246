#pragma once

// elevatorState holds the possible states of the elevator
enum elevatorState {IDLE, PREPARING_MOVE, MOVING_UP, MOVING_DOWN, ARRIVED};
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

    int floors = 4;
    int encoderPos = 2100;
    int doorOpenTime = 1000;
    float Kp = 0.1;
    float Ki = 0.003;
    float Kd = 0;

    int currentFloor = 1;
    bool anyRequests = false;

    int inData = 0;

    elevatorState state = IDLE;
    elevatorDirection direction = UP;
};