//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef DISK_QUEUE_H
#define DISK_QUEUE_H
#pragma once
class SimulationSystem;
class SimProcess;
#include <deque>
using namespace std;
class DiskQueue
{
private: 
	deque<SimProcess*> diskqueue;
	SimulationSystem* simsystem;
public:
	DiskQueue(SimulationSystem*);
	~DiskQueue(void);
	void add(SimProcess*);
	void pop();
	SimProcess* front();
	bool isEmpty();
	void status();
};
#endif

