//RYAN WEDGE -- 0876437 -- COSC 4330 -- SPRING 2015
#include "SimulationSystem.h"
int main(int argc, char** argv){
	SimulationSystem* simulator = new SimulationSystem();
	simulator->parseInstructions(); //get input from cin
	simulator->inputStatus(); //output how many processes were input
	simulator->loadProcessTable(); //load process table with processes
	simulator->setFormatting(); //set setw() formatting based on largest PID
	simulator->beginProcessing(); //execute process events
	return 0;
}
