// elevatorState holds the possible states of the elevator
enum elevatorState {IDLE, PREPARING_MOVE, MOVING_UP, MOVING_DOWN, ARRIVED};
enum elevatorDirection {UP, DOWN};

class StateMachine
{
private:
    
public:
    StateMachine();
    ~StateMachine();

    void idle();
    void prepareMove();
    void moveUp();
    void moveDown();
    void arrived();

    int floors = 4;
    int encoderPos = 2100;

    int currentFloor = 1;
    bool anyRequests = false;

    elevatorState state = IDLE;
    elevatorDirection direction = UP;
};