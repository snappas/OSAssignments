//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "QuadCore.h"
#include "SimulationSystem.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
//constructor
QuadCore::QuadCore(SimulationSystem* sys)
{
	totalUtilization = 0;
	simsystem = sys;
}
//destructor
QuadCore::~QuadCore(void)
{
}
//assign a process to a cpu core
bool QuadCore::useCore(SimProcess* p){
	stringstream message;
	message << "requests a core for " << p->getCurrentInstruction().getTime() << " ms";
	simsystem->detailedOutput(p->getPid(),message.str());
	message.str(string());
	if(!core1.getUsage()){
		core1.setProcess(p);
		p->setRunning();
		message << "added to CORE 1, releases at time " << p->getCurrentInstruction().getTime()+simsystem->getGlobalTime() << " ms";
		simsystem->detailedOutput(p->getPid(),message.str());
		return true;
	}
	if(!core2.getUsage()){
		core2.setProcess(p);
		p->setRunning();
		message << "added to CORE 2, releases at time " << p->getCurrentInstruction().getTime()+simsystem->getGlobalTime() << " ms";
		simsystem->detailedOutput(p->getPid(),message.str());
		return true;
	}
	if(!core3.getUsage()){
		core3.setProcess(p);
		p->setRunning();
		message << "added to CORE 3, releases at time " << p->getCurrentInstruction().getTime()+simsystem->getGlobalTime() << " ms";
		simsystem->detailedOutput(p->getPid(),message.str());
		return true;
	}
	if(!core4.getUsage()){
		core4.setProcess(p);
		p->setRunning();
		message << "added to CORE 4, releases at time " << p->getCurrentInstruction().getTime()+simsystem->getGlobalTime() << " ms";
		simsystem->detailedOutput(p->getPid(),message.str());
		return true;
	}
	simsystem->detailedOutput(p->getPid(),"must wait for a core");
	return false;
}
//increment time used by the process and total CPU time used
void QuadCore::incrementCpuTime(int t){
	if(core1.getUsage()){
		core1.incrementTime(t);
		totalUtilization += t;
	}
	if(core2.getUsage()){
		core2.incrementTime(t);
		totalUtilization += t;
	}
	if(core3.getUsage()){
		core3.incrementTime(t);
		totalUtilization += t;
	}
	if(core4.getUsage()){
		core4.incrementTime(t);
		totalUtilization += t;
	}
}
//output for the system status report
void QuadCore::status(){
	cout << "States of the CPU cores:\n";
	cout << " CORE1  ";
	if(core1.getUsage()){
		cout << "BUSY  PID " << core1.getPid() << "\n";
	}else{
		cout << "FREE  \n";
	}
	cout << " CORE2  ";
	if(core2.getUsage()){
		cout << "BUSY  PID " << core2.getPid() << "\n";
	}else{
		cout << "FREE  \n";
	}
	cout << " CORE3  ";
	if(core3.getUsage()){
		cout << "BUSY  PID " << core3.getPid() << "\n";
	}else{
		cout << "FREE  \n";
	}
	cout << " CORE4  ";
	if(core4.getUsage()){
		cout << "BUSY  PID " << core4.getPid() << "\n";
	}else{
		cout << "FREE  \n";
	}
}
//check how many available cores there are
int QuadCore::availableCores(){
	int numCores = 0;
	if(!core1.getUsage())
		numCores++;
	if(!core2.getUsage())
		numCores++;
	if(!core3.getUsage())
		numCores++;
	if(!core4.getUsage())
		numCores++;
	//cout << "Found " << numCores << " available cores." << endl;
	return numCores;
}
//check if an event is finished using a core
bool QuadCore::checkInstructionTime(){
	if(core1.getUsage()){
		if(core1.getCurrentTimeElapsed() == core1.getInstructionTime()){
			core1.setUsage(false);
			core1.getProcess()->setCurrentInstructionElapsed(0);
			simsystem->detailedOutput(core1.getProcess()->getPid(),"finished on CORE 1");
			core1.getProcess()->loadNextInstruction();
			return true;
		}
	}
	if(core2.getUsage()){
		if(core2.getCurrentTimeElapsed() == core2.getInstructionTime()){
			core2.setUsage(false);
			core2.getProcess()->setCurrentInstructionElapsed(0);
			simsystem->detailedOutput(core2.getProcess()->getPid(),"finished on CORE 2");
			core2.getProcess()->loadNextInstruction();
			return true;
		}
	}
	if(core3.getUsage()){
		if(core3.getCurrentTimeElapsed() == core3.getInstructionTime()){
			core3.setUsage(false);
			core3.getProcess()->setCurrentInstructionElapsed(0);
			simsystem->detailedOutput(core3.getProcess()->getPid(),"finished on CORE 3");
			core3.getProcess()->loadNextInstruction();
			return true;
		}
	}
	if(core4.getUsage()){
		if(core4.getCurrentTimeElapsed() == core4.getInstructionTime()){
			core4.setUsage(false);
			core4.getProcess()->setCurrentInstructionElapsed(0);
			simsystem->detailedOutput(core4.getProcess()->getPid(),"finished on CORE 4");
			core4.getProcess()->loadNextInstruction();
			return true;
		}
	}
	return false;
}
//return total CPU time used
int QuadCore::getTotalUtilization(){
	return totalUtilization;
}
