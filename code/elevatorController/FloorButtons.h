class FloorButton
{
private:
    int floorReq = [1,2,3,4,5,6,7]
    enum upOrDown = [u, d];
    

public:
    int floorRequest;
    FloorButton();

    ~FloorButton();

    // Read keyboard floor
    int readFloorBtn(int floorRequest);

    // Read keyboard up/down
    enum readUpDown(int upOrDown);   

    // Display choise
    int display();

};