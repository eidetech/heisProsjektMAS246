// elevatorState holds the possible states of the elevator
enum elevatorState {IDLE, PREPARING_MOVE, MOVING_UP, MOVING_DOWN};

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

    int floors = 4;
    int currentFloor = 1;

    elevatorState state = IDLE;
};