//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef INPUT_QUEUE_H
#define INPUT_QUEUE_H
#pragma once
class SimulationSystem;
class SimProcess;
#include <queue>
using namespace std;
class InputQueue
{
private: 
	queue<SimProcess*> inputqueue;
	SimulationSystem* simsystem;
public:
	InputQueue(SimulationSystem*);
	~InputQueue(void);
	void add(SimProcess*);
	void pop();
	SimProcess* front();
	bool isEmpty();
};
#endif

