#ifndef EMERGENCY_H
#define EMERGENCY_H
#pragma once
	
#define ENCODER_BTN 2
class Emergency  
{
	private:
		void readMecanicalEncoder_ISR();
	public:

		Emergency();
		~Emergency();

};
#endif