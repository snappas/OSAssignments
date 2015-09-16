//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "InputQueue.h"
#include "SimProcess.h"
#include "SimulationSystem.h"
#include <queue>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
//constructor
InputQueue::InputQueue(SimulationSystem* sys)
{
	simsystem = sys;
}
//destructor
InputQueue::~InputQueue(void)
{
}
//add process to the queue
void InputQueue::add(SimProcess* p){
	p->setWaiting();
	inputqueue.push(p);
	stringstream message;
	message << "added to Input Queue, size is now " << inputqueue.size();
	simsystem->detailedOutput(p->getPid(),message.str());
}
//remove process from the queue
void InputQueue::pop(){
	inputqueue.pop();
}
//get process at the front of the queue
SimProcess* InputQueue::front(){
	return inputqueue.front();
}
//check if queue is empty
bool InputQueue::isEmpty(){
	return inputqueue.empty();
}
