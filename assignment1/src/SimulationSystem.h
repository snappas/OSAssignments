//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef SIMULATION_SYSTEM_H
#define SIMULATION_SYSTEM_H
#pragma once
class QuadCore;
class IODevice;
class InputDevice;
class DiskQueue;
class ReadyQueue;
class InputQueue;
#include "ProcessTable.h"
#include "ProcessInput.h"
#include <queue>
#include <string>
using namespace std;
class SimulationSystem
{
private:
	QuadCore* CPU;
	InputDevice* INPUT;
	IODevice* DISK;
	ReadyQueue* RQ;
	DiskQueue* DQ;
	InputQueue* IQ;
	
	ProcessInput processInput;
	ProcessTable processTable;
	int globalTime;
	int MAX_PID_SIZE;
	int MAX_TIME_SIZE;

public:
	SimulationSystem(void);
	~SimulationSystem(void);
	void parseInstructions();
	void parseQueue(queue<string>);
	void inputStatus();
	void processStatus();
	void loadProcessTable();
	void loadReadyQueue();
	void beginProcessing();
	void checkRQ();
	void checkDQ();
	void checkIQ();
	void incrementTime(int);
	void outputReport();
	void computeCPUUtilization();
	int getGlobalTime();
	void detailedOutput(int,string);
	void setFormatting();
	void removeTerminated();
};
#endif
