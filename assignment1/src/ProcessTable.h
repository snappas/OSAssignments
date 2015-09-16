//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H
#pragma once
#include <vector>
#include "TableEntry.h"
using namespace std;
class ProcessTable
{
private:
	vector<TableEntry> pt;
public:
	ProcessTable(void);
	~ProcessTable(void);
	void newEntry(SimProcess*);
	bool checkIfDone();
	void removeTerminated();
	void status();
};
#endif

