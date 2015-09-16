//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "ReadyQueue.h"
#include "SimProcess.h"
#include "SimulationSystem.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
//constructor
ReadyQueue::ReadyQueue(SimulationSystem* sys)
{
	simsystem = sys;
}
//destructor
ReadyQueue::~ReadyQueue(void)
{
}
//add a process to the queue
void ReadyQueue::add(SimProcess* p){
	p->setReady();
	readyqueue.push_back(p);
	stringstream message;
	message << "added to Ready Queue, size is now " << readyqueue.size();
	simsystem->detailedOutput(p->getPid(),message.str());
}
//remove a process from the queue
void ReadyQueue::pop(){
	readyqueue.pop_front();
}
//get the process at the front of the queue
SimProcess* ReadyQueue::front(){
	return readyqueue.front();
}
//check if queue is empty
bool ReadyQueue::isEmpty(){
	return readyqueue.empty();
}
//output for system status report
void ReadyQueue::status(){
	cout << "CPU QUEUE: ";
	if(isEmpty()){
		cout << "-- \n";
	}else{
		cout << "\n";
		for(unsigned int i = 0; i<readyqueue.size();i++){
			cout << " PID " << readyqueue[i]->getPid() << " ";
		}
		cout << "\n";
	}
}
