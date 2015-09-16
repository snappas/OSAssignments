//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "ProcessInput.h"
#include "SimProcess.h"
#include <iostream>
#include <cmath>
using namespace std;
//constructor
ProcessInput::ProcessInput(void)
{
}
//destructor
ProcessInput::~ProcessInput(void)
{
}
//add process to the container
void ProcessInput::pushProcess(SimProcess* p){
	processes.push_back(p);
}
//add events to the process
void ProcessInput::pushInstructionToBack(string name, int time){
	if(!processes.empty()){
		processes.back()->pushInstruction(name,time);
	}else{
		cout << "Error: Cannot add instruction to empty process container!\n";
	}
}
//get the number of processes in the container
int ProcessInput::getProcessCount(){
	return processes.size();
}
//flag to see if the container is empty
bool ProcessInput::isEmpty(){
	return processes.empty();
}
//get the process at the front of the container
SimProcess* ProcessInput::getFront(){
	return processes.front();
}
//output for information about processes in the input
void ProcessInput::status(){
	cout << "Processes in Input: " << getProcessCount() << "\n";
	for(int i = 0; i<getProcessCount(); i++){
		cout << "Process " << processes[i]->getPid() << ":\t Events: " << processes[i]->getInstructionCount() << "\t Start Time: " << processes[i]->getStartTime() << "\n";
	}
}
//get the process id at an index
int ProcessInput::getProcessPidAt(int i){
	return processes.at(i)->getPid();
}
//get the process at an index
SimProcess* ProcessInput::getAt(int i){
	return processes[i];
}
//find the largest pid in the input
int ProcessInput::largestPID(){
	int largest = 0;
	for(unsigned int i = 0; i<processes.size();i++){
		if(processes.at(i)->getPid() > largest){
			largest = processes.at(i)->getPid();
		}
	}
	return largest;
}
//count the number of digits in a number
int ProcessInput::numDigits(int x){
	x = abs(x);
	return (x < 10 ? 1 :
		(x < 100 ? 2 :
		(x < 1000 ? 3 :
		(x < 10000 ? 4 :
		(x < 100000 ? 5 :
		(x < 1000000 ? 6 :
		(x < 10000000 ? 7 :
		(x < 100000000 ? 8 :
		(x < 1000000000 ? 9 :
		10)))))))));
}
//find the total amount of time the events require for each process
int ProcessInput::totalTime(){
	int x = 0;
	for(unsigned int i = 0; i< processes.size();i++){
		x += processes.at(i)->getTotalInstructionsTime();
	}
	return x;
}
