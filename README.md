# heisProsjektMAS246

This program together with the "All in one servo lab" (AISL), simulates an elevator that moves between 7 
floors. To start the simulation upload elevatorController.ino to AISL. Then open serial monitor in 
Arduino ide.

At each floor unless 1. and last there are an up and down button. Theese are represented
by keyboard keys [u] and [d], and are controlled via serial monitor.  

1. [u]
2. [u] [d]
3. [u] [d]
4. [u] [d]
5. [u] [d]
6. [u] [d]
7.     [d]

To request the elevator. Select current floor you are in by entering 1-7 in serial monitor and press [RETURN]
Then enter desired direction. LCD screen hold information about the cabs current position and 
direction.

|'''''''''''''''''''|
|     Up ---->      |
|     1. floor      |
|...................|


The elevator will shortly arrive at selected floor and doors will open.

When inside cab added weight to the cab can be simulated by adjusting the left knob (POT) on the AISL.
Total weigth and "OVERLOAD" alarm will flash on LCD-screen if weigth is over 1400 kg.
 
|'''''''''''''''''''|
|      1450kg	    |
|    -OVERLOAD-     |
|...................|

To select the floor you want to go to the buttons 1-7 shall be pressed. The LED ligth above the selected 
button will ligth up.

The LEDs will also show the queue in the direction the elevator is moving.

|''''''''''''''''''''''''''''''''''''''''|
| [ ]  [*]  [ ]  [*]  [ ]  [ ]  [ ]  [ ] |  <- LED		
|  7	6    5    4    3    2    1    0  |
|					                     | 
|  o    o    o    o    o    o    o    o  |  <- Red buttons
|........................................|

The cab will stop in all requested floors until it reaches the top or the bottom and then switch direction.


--Settings:

	Numbers of floor		    floors			    stateMachine.h
 	Distance beetween floors	endcoderPos		    stateMachine.h
 	Time door is open??					            stateMachine.h
 	PID tuning			        Kp, Ki, Kd		    stateMachine.h

--Display:
	All messages displayed in LCD and terminal 		Dispaly.cpp
	
--Oveload:
	Set max weigt						            overload.h


			
		




 			    


