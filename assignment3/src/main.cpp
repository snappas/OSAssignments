//Ryan Wedge -- COSC 4330 -- Spring 2015

#include <iostream>
#include <cstdlib>
#include <sstream>
#include "postoffice.h"

using namespace std;

int main(int argc, char** argv)
{
    int numClerks;
    if(argc != 2){
        cout << "Error: invalid number of arguments\n";
        exit(1);
    }else{
        istringstream iss(argv[1]);
        iss >> numClerks; // parse argv for number of clerks
    }
    const char sem_clerks[] = "rjw_clerks";
    const char sem_mutex[] = "rjw_mutex";
    const int key_mem = 876437;

    PostOffice postOffice;
    postOffice.getInput();
    postOffice.createSemaphore(sem_clerks,numClerks);
    postOffice.createSemaphore(sem_mutex,1);
    postOffice.createSharedSegment(key_mem,sizeof(int));
    postOffice.processCustomers(sem_clerks,sem_mutex,key_mem);
    postOffice.printStatistics(key_mem);
    postOffice.removeSharedSegment(key_mem,sizeof(int));
    postOffice.removeSemaphore(sem_clerks);
    postOffice.removeSemaphore(sem_mutex);
    return 0;
}


