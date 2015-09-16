//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "IODevice.h"
#include "SimulationSystem.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
//constructor
IODevice::IODevice(SimulationSystem* sys)
{
	inUse = false;
	pid = -1;
	simsystem = sys;
}
//destructor
IODevice::~IODevice(void)
{
}
//check if the elapsed time is equal to the required time by the event
bool IODevice::checkInstructionTime(){
	if(inUse){
		if(currentProcess->getCurrentInstruction().getTime() == currentProcess->getCurrentInstructionElapsed()){
			simsystem->detailedOutput(currentProcess->getPid(),"finished on DISK component");
			currentProcess->setCurrentInstructionElapsed(0);
			inUse = false;
			currentProcess->loadNextInstruction(); //FINISHED INSTRUCTION: LOAD NEW ONE -- LOADS PROCESS INTO PROPER QUEUE
			return true;
		}
	}
	return false;
}
//increment time used by the process for the event
void IODevice::incrementDiskTime(int t){
	if(inUse){
		currentProcess->setCurrentInstructionElapsed(currentProcess->getCurrentInstructionElapsed()+t);
	}
}
//use the disk if it's not in use
bool IODevice::useDisk(SimProcess* p){
	if(inUse){
		return false;
	}else{
		currentProcess = p;
		stringstream message;
		message << "added to DISK for " << p->getCurrentInstruction().getTime() << " ms, releases at time "
			    << p->getCurrentInstruction().getTime()+simsystem->getGlobalTime() << " ms";
		simsystem->detailedOutput(p->getPid(),message.str());
		currentProcess->setWaiting();
		inUse = true;
		return true;
	}
}
//get the flag to see if it's in use
bool IODevice::getUsage(){
	if(inUse){
		return true;
	}else{
		return false;
	}
}
//get the process id currently using the device
int IODevice::getPid(){
	if(inUse){
		return currentProcess->getPid();
	}else{
		return -1;
	}
}
//output for the system status report
void IODevice::status(){
	cout << "State of the Disk:\n";
	cout << " DISK is ";
	if(inUse){
		cout << "BUSY  PID ";
		cout << getPid() << "\n";
	}else{
		cout << "IDLE  \n";
	}
}
