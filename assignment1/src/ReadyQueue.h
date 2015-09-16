//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef READY_QUEUE_H
#define READY_QUEUE_H
#pragma once
class SimulationSystem;
class SimProcess;
#include <deque>
using namespace std;
class ReadyQueue
{
private:
	deque<SimProcess*> readyqueue;
	SimulationSystem* simsystem;
public:
	ReadyQueue(SimulationSystem*);
	~ReadyQueue(void);
	void add(SimProcess*);
	SimProcess* front();
	void pop();
	bool isEmpty();
	void status();
};
#endif

