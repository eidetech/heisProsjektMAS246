class CabButtons
{
private:
    // Array for storing input data when 
    int btnRead[9];

    
    int buttonNumber;
    // Variable for storing digitalRead of buttons
    int readInput;
public:
     
    
    // Constructor
    CabButtons();

    // Destructor
    ~CabButtons();

    // Read any tactile button
    int readTactBtn(int buttonNumber);

    // Read the encoder button
    int readEncBtn();

    void displayBtnInput();
};
