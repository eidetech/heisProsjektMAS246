#ifndef DISPLAY_H
#define DISPLAY_H
#pragma once
	
class Display  
{
	private:

	public:

		Display();
		~Display();

	// Display
    void displayDefaultScreen();
    void displayMovingUp();
    void displayMovingDown();
	void displayOpeningDoors();
	void displayClosingDoors();
    void createSpecialChars();

	void clearDisplay();

};
#endif