//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "Instruction.h"
#include <string>
using namespace std;
//constructor
Instruction::Instruction(void)
{
	name = "";
	time = -1;
}
//destructor
Instruction::~Instruction(void)
{
}
//overloaded constructor
Instruction::Instruction(string n, int t){
	name = n;
	time = t;
}
//get the name of the event
string Instruction::getName(){
	return name;
}
//get the required time by the event
int Instruction::getTime(){
	return time;
}
//set the name of the event
void Instruction::setName(string n){
	name = n;
}
//set the time required by the event
void Instruction::setTime(int t){
	time = t;
}
