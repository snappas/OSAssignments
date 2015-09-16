//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef CPU_CORE_H
#define CPU_CORE_H
#pragma once
#include "SimProcess.h"

class CPUCore
{
private:
	SimProcess* processing;
	bool inUse;
	int pid;
public:
	CPUCore(void);
	~CPUCore(void);
	void incrementTime(int);
	bool setProcess(SimProcess*);
	void setUsage(bool);
	bool getUsage();
	int getInstructionTime();
	int getCurrentTimeElapsed();
	int getPid();
	SimProcess* getProcess();
};
#endif

