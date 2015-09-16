//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "DiskQueue.h"
#include "SimProcess.h"
#include "SimulationSystem.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
//constructor
DiskQueue::DiskQueue(SimulationSystem* sys)
{
	simsystem = sys;
}
//destructor
DiskQueue::~DiskQueue(void)
{
}
//add process to the queue
void DiskQueue::add(SimProcess* p){
	p->setWaiting();
	diskqueue.push_back(p);
	stringstream message;
	message << "added to Disk Queue, size is now " << diskqueue.size();
	simsystem->detailedOutput(p->getPid(),message.str());
}
//remove process from the queue
void DiskQueue::pop(){
	diskqueue.pop_front();
}
//get the process at the front of the queue
SimProcess* DiskQueue::front(){
	return diskqueue.front();
}
//check if queue is empty
bool DiskQueue::isEmpty(){
	return diskqueue.empty();
}
//output for the system status report
void DiskQueue::status(){
	cout << "DISK QUEUE: ";
	if(isEmpty()){
		cout << "--\n";
	}else{
		cout << "\n";
		for(unsigned int i = 0; i<diskqueue.size();i++){
			cout << "PID " << diskqueue[i]->getPid() << " ";
		}
		cout << "\n";
	}
}
