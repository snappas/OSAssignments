//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "InputDevice.h"
#include "SimulationSystem.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
//constructor
InputDevice::InputDevice(SimulationSystem* sys)
{
	simsystem = sys;
	inUse = false;
}
//destructor
InputDevice::~InputDevice(void)
{
}
//check if the elapsed time on the process equals the required time by the event
bool InputDevice::checkInstructionTime(){
	if(inUse){
		if(currentProcess->getCurrentInstruction().getTime() == currentProcess->getCurrentInstructionElapsed()){
			simsystem->detailedOutput(currentProcess->getPid(),"finished on INPUT component");
			currentProcess->setCurrentInstructionElapsed(0);
			inUse = false;
			currentProcess->loadNextInstruction(); //FINISHED INSTRUCTION: LOAD NEW ONE -- LOADS PROCESS INTO PROPER QUEUE
			return true;
		}
	}
	return false;
}
//increment time on the process
void InputDevice::incrementInputTime(int t){
	if(inUse){
		currentProcess->setCurrentInstructionElapsed(currentProcess->getCurrentInstructionElapsed()+t);
	}
}
//check flag to see if device is in use
bool InputDevice::getUsage(){
	return inUse;
}
//assign process to the device
bool InputDevice::useInput(SimProcess* p){
	if(!inUse){
		currentProcess = p;
		currentProcess->setWaiting();
		stringstream message;
		message << "added to INPUT for "<< p->getCurrentInstruction().getTime() << " ms, releases at time "
			    << p->getCurrentInstruction().getTime()+simsystem->getGlobalTime() << " ms\n";
		simsystem->detailedOutput(p->getPid(),message.str());
		inUse = true;
		return true;
	}
	return false;
}
