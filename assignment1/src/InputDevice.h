//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H
#pragma once
class SimulationSystem;
#include "SimProcess.h"

class InputDevice
{
private:
	SimProcess* currentProcess;
	bool inUse;
	SimulationSystem* simsystem;
public:
	InputDevice(SimulationSystem*);
	~InputDevice(void);
	void incrementInputTime(int);
	bool checkInstructionTime();
	bool useInput(SimProcess* p);
	bool getUsage();
};
#endif

