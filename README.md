 Vertical express 1.4.1 (latest release)
 -
This is an Arduino code that together with the "All in One Servo Lab" (AISL) hardware, simulates an elevator that moves between 4 floors. First you need to download and extract elevatorController folder to your computer.
To start the simulation open the elevatorController.ino and upload the code to an AISL unit. Make sure that all the .cpp and .h files from the folder appears as tabs in the Arduino IDE. 
Then open serial monitor. Set correct baudrate (9600) **and choose the no line ending option (important)**.


At each floor except 1. and 4. there is an up and a down button. These are represented by keyboard keys [u] (up) and [d] (down), and they are controlled via serial monitor.  

1. [u]
2. [u] [d]
3. [u] [d]
4. [d]


To request the elevator, select which direction you want to go [u/d]. Then enter the current floor you are standing in by entering numbers 1-4 in the serial monitor and press [RETURN]

The elevator will shortly arrive at selected floor and doors will open.

<img src="demo.png" width="400"/>

To simulate weight you can adjust the right potentiometer knob on the lab unit. If the weight is above the set limit an alarm will flash on the LCD screen when requesting floors from inside the cab.

To select the floor you want to go to the buttons 1-4 may be pressed. The LED light above the selected button will light up.

The LED's will also show the requested queue in the direction the elevator is moving.

The cab will stop in all requested floors until it reaches the top or the bottom and then switch direction.


Settings
-
There is a number of settings that can be tweaked in the software for scalability and compatibility.

|Setting|Variable|File
|--|--|--|
|Number of floors|floors|StateMachine.h|
|Distance between floors|encoderPos|StateMachine.h|
|Time door is open|doorTime|StateMachine.h|
|PID settings|Kp, Ki, Kd|StateMachine.h|
|Set weight limit|setWeight|Overload.h
