class FloorButton
{
private:

public:
    int floorRequest = 0;
    int input;

    FloorButton();
    ~FloorButton();

    // Read floor from keyboard
    int readFloorBtn();

    // Read U/D key from keyboard
    int readUpDown();
};
