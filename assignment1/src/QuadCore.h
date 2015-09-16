//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef QUAD_CORE_H
#define QUAD_CORE_H
#pragma once
class SimulationSystem;
#include "CPUCore.h"
#include "SimProcess.h"
class QuadCore
{
private:
	CPUCore core1;
	CPUCore core2;
	CPUCore core3;
	CPUCore core4;
	int totalUtilization;
	SimulationSystem* simsystem;
public:
	QuadCore(SimulationSystem*);
	~QuadCore(void);
	void incrementCpuTime(int);
	bool checkInstructionTime();
	bool useCore(SimProcess*);
	int availableCores();
	int getTotalUtilization();
	int core1Pid();
	int core2Pid();
	int core3Pid();
	int core4Pid();
	void status();
};
#endif
