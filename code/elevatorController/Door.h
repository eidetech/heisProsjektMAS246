
enum doorState
{
    OPEN = 0,
    MOVING = 1,
    CLOSED = 2
};

class Door
{
private:
    int doorMoveLength = 200;
    
public:
    Door();
    ~Door();

    void open();
    void close();
    void doorDisable();
};
