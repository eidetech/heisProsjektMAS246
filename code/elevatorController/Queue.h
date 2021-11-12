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

    void printRequests();

    int upRequests[4] = {0, 0, 0, 0};
    int downRequests[4] = {0, 0, 0, 0};
    
    int floors = 4;
};