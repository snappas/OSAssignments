//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "SimProcess.h"
#include "Instruction.h"
#include "ReadyQueue.h"
#include "DiskQueue.h"
#include "InputQueue.h"
#include "SimulationSystem.h"
#include <string>
#include <queue>
#include <deque>
#include <iostream>
#include <iomanip>

using namespace std;
//constructor
SimProcess::SimProcess(void)
{
}
//destructor
SimProcess::~SimProcess(void)
{
}
//constructor
SimProcess::SimProcess(int id): startTime(0){
	cpuTime = 0;
	currentInstructionElapsed = 0;
	pid = id;
}
//constructor
SimProcess::SimProcess(int id, int time,SimulationSystem* sys){
	cpuTime = 0;
	pid = id;
	startTime = time;
	currentInstructionElapsed = 0;
	simsystem = sys;
}
//set the start time of the process
void SimProcess::setStartTime(int time){
	startTime = time;
}
//add event to the process
void SimProcess::pushInstruction(string name,int time){
	Instruction newInstruction(name,time);
	instructions.push_back(newInstruction);
}
//return size of event queue
int SimProcess::getInstructionCount(){
	return instructions.size();
}
//return process id of the process
int SimProcess::getPid(){
	return pid;
}
//return how much cpu time this process has used
int SimProcess::getCpuTime(){
	return cpuTime;
}
//set the cpu time this process has used
void SimProcess::setCpuTime(int t){
	cpuTime = t;
}
//return the start time of this process
int SimProcess::getStartTime(){
	return startTime;
}
//load the next event in the queue
bool SimProcess::loadNextInstruction(){
	if(!instructions.empty()){
		currentInstruction.setName(instructions.front().getName());
		currentInstruction.setTime(instructions.front().getTime());
		instructions.pop_front();
		if(currentInstruction.getName().compare("CPU") == 0){
			RQ->add(this);
			return true;
		}else if(currentInstruction.getName().compare("I/O") == 0){
			if(currentInstruction.getTime() == 0){
				simsystem->detailedOutput(pid,"requests disk access for 0 ms");
				simsystem->detailedOutput(pid,"accesses the disk buffer");
				loadNextInstruction();
				return true;
			}
			DQ->add(this);
			return true;
		}else if(currentInstruction.getName().compare("INPUT") == 0){
			IQ->add(this);
			return true;
		}
		return true;
	}else{
		simsystem->detailedOutput(pid,"terminated");
		this->setTerminated();
		simsystem->outputReport();
		simsystem->removeTerminated();
		return false;
	}
}
//get the current event loaded in the process
Instruction SimProcess::getCurrentInstruction(){
	return currentInstruction;
}
//get the time elapsed by the current event
int SimProcess::getCurrentInstructionElapsed(){
	return currentInstructionElapsed;
}
//set the time elapsed by the current event
void SimProcess::setCurrentInstructionElapsed(int t){
	currentInstructionElapsed = t;
}
//make the process aware of the queues it can go to
void SimProcess::setQueues(ReadyQueue* rq ,DiskQueue* dq ,InputQueue* iq){
	RQ = rq;
	DQ = dq;
	IQ = iq;
}
//process states
void SimProcess::setReady(){
	currentStatus = "READY";
}
void SimProcess::setWaiting(){
	currentStatus = "WAITING";
}
void SimProcess::setTerminated(){
	currentStatus = "TERMINATED";
}
void SimProcess::setRunning(){
	currentStatus = "RUNNING";
}
//return the current process state
string SimProcess::getStatus(){
	return currentStatus;
}
//make the process aware of the system it's in
void SimProcess::setSystem(SimulationSystem* sys){
	simsystem = sys;
}
//find out total time the events will take
int SimProcess::getTotalInstructionsTime(){
	int sum = 0;
	for(unsigned int i = 0; i<instructions.size();i++){
		sum += instructions[i].getTime();
	}
	return sum;
}
