class LED
{
private:
    
public:
    // Constructor
    LED();

    // Destructor
    ~LED();

    // Turn on all LED's in sequence
    void lightUpSeq();

    // Turn on specific LED
    void on(int led);

    // Turn off specific LED
    void off(int led);

    // Blink all leds for emergency stop
    void blinkAllLeds();
};
