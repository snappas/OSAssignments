//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "ProcessTable.h"
#include "TableEntry.h"
#include <iostream>
#include <string>
using namespace std;
//constructor
ProcessTable::ProcessTable(void)
{
}
//destructor
ProcessTable::~ProcessTable(void)
{
}
//add a process to the table
void ProcessTable::newEntry(SimProcess* p){
	TableEntry newTableEntry(p);
	pt.push_back(newTableEntry);
}
//output for the system status report
void ProcessTable::status(){
	cout << "PROCESS TABLE:\n";
	cout << " PID   ST  CPUTIME   STATUS\n" ;
	for(unsigned int i = 0; i < pt.size(); i++){
		pt[i].showEntry();
	}
}
//check if all processes are terminated
bool ProcessTable::checkIfDone(){
	int x = 0;
	for(unsigned int i = 0; i<pt.size();i++){
		if(pt[i].getStatus().compare("TERMINATED")==0){
			x++;
		}
	}
	if((unsigned int)x == pt.size()){
		return true;
	}else{
		return false;
	}
}
//remove terminated processes from the table
void ProcessTable::removeTerminated(){
	for(unsigned int i = 0; i<pt.size();i++){
		if(pt[i].getStatus().compare("TERMINATED")==0){
			pt.erase(pt.begin()+i);
		}
	}
}

