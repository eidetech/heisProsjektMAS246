class FloorButton
{
private:

public:
    int floorRequest;
    int input;

    FloorButton();
    ~FloorButton();

    // Read floor from keyboard
    int readFloorBtn();

    // Read U/D key from keyboard
    int readUpDown()
};