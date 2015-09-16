//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef SIM_PROCESS_H
#define SIM_PROCESS_H
#pragma once
class ReadyQueue;
class DiskQueue;
class InputQueue;
class SimulationSystem;
#include <string>
#include <queue>
#include <deque>
#include "Instruction.h"
using namespace std;
class SimProcess
{
private:
	int pid;
	int startTime;
	int cpuTime;
	int currentInstructionElapsed;
	Instruction currentInstruction;
	deque<Instruction> instructions;
	ReadyQueue* RQ;
	DiskQueue* DQ;
	InputQueue* IQ;
	string currentStatus;
	SimulationSystem* simsystem;
public:
	SimProcess(int);
	SimProcess(int,int,SimulationSystem*);
	SimProcess(void);
	~SimProcess(void);
	bool loadNextInstruction();
	void pushInstruction(string, int);
	void setQueues(ReadyQueue* ,DiskQueue* ,InputQueue*);
	void setSystem(SimulationSystem*);
	void setStartTime(int);
	void setCpuTime(int);
	void setCurrentInstructionElapsed(int);
	void setReady();
	void setWaiting();
	void setTerminated();
	void setRunning();
	int getStartTime();
	int getPid();
	int getCurrentInstructionElapsed();
	int getCpuTime();
	int getInstructionCount();
	int getTotalInstructionsTime();
	Instruction getCurrentInstruction();
	string getStatus();
};
#endif

