#include "StateMachine.h"

class Queue
{
private:
    
public:
    Queue();
    ~Queue();
    
    int floors = 4;
    int floorRequests[4][3];
    int requests[4] = {0, 0, 0, 0};
    
    int add(int floorNum);
    int remove(int floorNum);
    void printRequests();

    void initFloorRequests();
    void printFloorRequests();
    void addToFloorRequests(int floor, elevatorDirection dir);
    void removeFromFloorRequests(int floor, elevatorDirection dir);
};