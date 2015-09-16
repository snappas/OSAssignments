//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef TABLE_ENTRY_H
#define TABLE_ENTRY_H
#pragma once
#include <string>
#include "SimProcess.h"

using namespace std;
class TableEntry
{
private:
	SimProcess* processEntry;
public:
	TableEntry(SimProcess*);
	TableEntry(void);
	~TableEntry(void);
	void showEntry();
	void setProcess(SimProcess*);
	SimProcess* getProcess();
	string getStatus();
};
#endif

