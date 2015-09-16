//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "SimulationSystem.h"
#include "SimProcess.h"
#include "QuadCore.h"
#include "IODevice.h"
#include "InputDevice.h"
#include "ReadyQueue.h"
#include "DiskQueue.h"
#include "InputQueue.h"
#include <string>
#include <iostream>
#include <queue>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <iomanip>
using namespace std;
//constructor
SimulationSystem::SimulationSystem(void)
{
	globalTime = 0;
	MAX_PID_SIZE = 0;
	MAX_TIME_SIZE = 0;
	RQ = new ReadyQueue(this);
	DQ = new DiskQueue(this);
	IQ = new InputQueue(this);
	CPU = new QuadCore(this);
	DISK = new IODevice(this);
	INPUT = new InputDevice(this);
}
//destructor
SimulationSystem::~SimulationSystem(void)
{
}
//store each line of input into a container
void SimulationSystem::parseInstructions(){
	std::string input;
	queue<string> processQueue;
	while(getline(cin, input)){
		istringstream iss(input);
		ostringstream oss;
		string instruction = "";
		int time = 0;
		iss >> instruction >> time;
		oss << instruction << " " << time;
		processQueue.push(oss.str());
	}
	parseQueue(processQueue);
}
//process the container of input into simprocess objects, store them in a new container
void SimulationSystem::parseQueue(queue<string> allQueue){
	istringstream ss;
	string instruction = "";
	int time = 0;
	int pid = -1;
	while(!allQueue.empty()){
		ss.clear();
		ss.str(allQueue.front());
		instruction.clear();
		time = 0;
		ss >> instruction >> time;
		transform(instruction.begin(),instruction.end(),instruction.begin(),(int(*)(int))toupper);
		if(instruction.compare("NEW") == 0){
			pid = time;
			allQueue.pop();
			ss.clear();
			ss.str(allQueue.front());
			instruction = "";
			time = 0;
			ss >> instruction >> time;
			transform(instruction.begin(),instruction.end(),instruction.begin(),(int(*)(int))toupper);
			if(instruction.compare("START") == 0){
				processInput.pushProcess(new SimProcess(pid,time,this));
				allQueue.pop();
			}else{
				cout << "Error: NEW is not followed by START\n";
				break;
			}
		}else{
			processInput.pushInstructionToBack(instruction,time);
			allQueue.pop();
		}
	}	
}
//output information about the process input
void SimulationSystem::inputStatus(){
	processInput.status();
}
//output the process table for system status report
void SimulationSystem::processStatus(){
	processTable.status();
}
//load the process table with the simprocess objects
void SimulationSystem::loadProcessTable(){
	for(int i = 0;i < processInput.getProcessCount(); i++){
		processTable.newEntry(processInput.getAt(i));
	}
}
//put a process into the ready queue
void SimulationSystem::loadReadyQueue(){
	for(int i = 0; i<processInput.getProcessCount();i++){
		if(processInput.getAt(i)->getStartTime() == globalTime){
			processInput.getAt(i)->setQueues(RQ,DQ,IQ);
			processInput.getAt(i)->loadNextInstruction();
		}
	}
}
//execute the events in the process objects
void SimulationSystem::beginProcessing(){
	if(!processInput.isEmpty()){
		while(1){
			//load processes into ready queue at their start time
			loadReadyQueue();
			//check components if the duration of the instruction is finished
			DISK->checkInstructionTime();
			INPUT->checkInstructionTime();
			CPU->checkInstructionTime();
			//check queues if there is a process available
			checkRQ();
			checkDQ();
			checkIQ();
			//increment elapsed time on process, total elapsed time, time used on cpu
			incrementTime(1);
			//check if all processes are terminated
			if(processTable.checkIfDone()){
				cout << "Finished simulation\n";
				break;
			}
		}
	}
}
//increment time elapsed by the system and its components
void SimulationSystem::incrementTime(int t){
	globalTime += t;
	CPU->incrementCpuTime(t);
	DISK->incrementDiskTime(t);
	INPUT->incrementInputTime(t);
}
//check if the ready queue has a process that can go into the cpu
void SimulationSystem::checkRQ(){
	if(!RQ->isEmpty()){
		if(RQ->front()->getStartTime() <= globalTime){ //check if process at front of queue should start before or at current time
			if(RQ->front()->getCurrentInstruction().getName().compare("CPU") == 0){ //check if current loaded instruction is CPU type
				if(CPU->availableCores() > 0){ //check if there are available cores
					if(CPU->useCore(RQ->front())){ //assign core to use SimProcess
						RQ->pop(); //remove SimProcess from RQ
					}
				}
			}
		}
	}
}
//check the disk queue to see if a process can use the disk
void SimulationSystem::checkDQ(){
	if(!DQ->isEmpty()){
		if(!DISK->getUsage()){
			if(DISK->useDisk(DQ->front())){
				DQ->pop();
			}
		}
	}
}
//check the input queue to see if a process can use the input device
void SimulationSystem::checkIQ(){
	if(!IQ->isEmpty()){
		if(!INPUT->getUsage()){
			if(INPUT->useInput(IQ->front())){
				IQ->pop();
			}
		}
	}
}
//output the report when a process terminates
void SimulationSystem::outputReport(){
	cout << "\nCURRENT STATE OF THE SYSTEM:\n";
	cout << "Total time elapsed: " << globalTime << " ms\n";
	CPU->status();
	DISK->status();
	computeCPUUtilization();
	RQ->status();
	DQ->status();
	processTable.status();
	cout << "\n";
}
//calculate load average
void SimulationSystem::computeCPUUtilization(){
	double utilization = 0;
	utilization = (double)CPU->getTotalUtilization() / (double)globalTime;
	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(3);
	cout << "Average number of busy cores: " << utilization << "\n";
}
//return total elapsed time by the simulation
int SimulationSystem::getGlobalTime(){
	return globalTime;
}
//helper function to display detailed information with a simulated timestamp about a process
void SimulationSystem::detailedOutput(int pid, string message){
	cout << "[ " << setw(MAX_TIME_SIZE) << globalTime <<"ms " << "] " << "PID " << setw(MAX_PID_SIZE) << pid  << " " << message << "\n";
}
//set the widths for setw()
void SimulationSystem::setFormatting(){
	MAX_PID_SIZE = processInput.numDigits(processInput.largestPID());
	MAX_TIME_SIZE = processInput.numDigits(processInput.totalTime());
}
//remove terminated processes from the process table
void SimulationSystem::removeTerminated(){
	processTable.removeTerminated();
}
