//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "TableEntry.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
//constructor
TableEntry::TableEntry(SimProcess* p){
	processEntry = p;
}
//constructor
TableEntry::TableEntry(void)
{
}
//destructor
TableEntry::~TableEntry(void)
{
}
//output information about the process in the table
void TableEntry::showEntry(){
	cout << setw(4) << processEntry->getPid() << setw(5) << processEntry->getStartTime()  << "  "
		 << setw(5) << processEntry->getCpuTime() << setw(12) << processEntry->getStatus() << "\n";
}
//return process state
string TableEntry::getStatus(){
	return processEntry->getStatus();
}
