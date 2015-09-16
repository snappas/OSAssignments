//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H
#pragma once
#include <deque>
#include <string>
#include "SimProcess.h"
using namespace std;
class ProcessInput
{
private:
	deque<SimProcess*> processes; 
public:
	ProcessInput(void);
	~ProcessInput(void);
	void pushProcess(SimProcess*);
	void pushInstructionToBack(string, int);
	bool isEmpty();
	int getProcessCount();
	SimProcess* getFront();
	SimProcess* getAt(int);
	int getProcessPidAt(int);
	int largestPID();
	int numDigits(int);
	int totalTime();
	void status();
};
#endif
