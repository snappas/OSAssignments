//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#pragma once
#include <string>
using namespace std;
class Instruction
{
private:
	string name;
	int time;
public:
	Instruction(string,int);
	Instruction(void);
	~Instruction(void);
	void setTime(int);
	void setName(string);
	string getName();
	int getTime();
};
#endif

