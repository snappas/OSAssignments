//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef IO_DEVICE_H
#define IO_DEVICE_H
#pragma once
class SimulationSystem;
#include "SimProcess.h"
class IODevice
{
private:
	SimProcess* currentProcess;
	bool inUse;
	int pid;
	SimulationSystem* simsystem;
public:
	IODevice(SimulationSystem*);
	~IODevice(void);
	void incrementDiskTime(int);
	bool checkInstructionTime();
	bool useDisk(SimProcess* p);
	int getPid();
	bool getUsage();
	void status();
};
#endif

