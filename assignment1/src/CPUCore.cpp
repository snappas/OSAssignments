//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "CPUCore.h"
#include "SimProcess.h"

//constructor
CPUCore::CPUCore(void){
	inUse = false;
	pid = -1;
}
//destructor
CPUCore::~CPUCore(void)
{
}
//assign process to this core if not in use
bool CPUCore::setProcess(SimProcess* proc){
	if(inUse){
		return false;
	}else{
		processing = proc;
		inUse = true;
		pid = proc->getPid();
		return true;
	}
}
//set flag to see if core is in use
void CPUCore::setUsage(bool setUse){
	inUse = setUse;
}
//get flag to see if core is in use
bool CPUCore::getUsage(){
	return inUse;
}
//increment process time elapsed and total CPU time used by CPU
void CPUCore::incrementTime(int t){
	processing->setCpuTime(processing->getCpuTime()+t);
	processing->setCurrentInstructionElapsed(processing->getCurrentInstructionElapsed()+t);
}
//get elapsed time on core for the event
int CPUCore::getCurrentTimeElapsed(){
	return processing->getCurrentInstructionElapsed();
}
//get time required by the event
int CPUCore::getInstructionTime(){
	return processing->getCurrentInstruction().getTime();
}
//get current pid on the core
int CPUCore::getPid(){
	return pid;
}
//get the process currently in the core
SimProcess* CPUCore::getProcess(){
	return processing;
}
