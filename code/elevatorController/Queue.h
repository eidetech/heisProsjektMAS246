#include "StateMachine.h"

class Queue
{
private:
    
public:
    Queue();
    ~Queue();

    int addUp(int floorNum);
    int addDown(int floorNum);

    int removeUp(int floorNum);
    int removeDown(int floorNum);

    int upRequests[4] = {0, 0, 0, 0};
    int downRequests[4] = {0, 0, 0, 0};
    
    int floors = 4;
    
    // Testing new queue system
    int requests[4] = {0, 0, 0, 0};
    int add(int floorNum);
    int remove(int floorNum);
    void printRequests();

    int floorRequests[4][3];

    void initFloorRequests();
    void printFloorRequests();
    void addToFloorRequests(int floor, elevatorDirection dir);
    void removeFromFloorRequests(int floor, elevatorDirection dir);
};