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
