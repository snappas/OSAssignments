//Ryan Wedge -- COSC 4330 -- Spring 2015

#ifndef POSTOFFICE_H
#define POSTOFFICE_H
#include <queue>
#include "customer.h"
#include <semaphore.h>
#include <map>
using namespace std;
class PostOffice
{
private:
    int numClerks;
    int numServiced;
    queue<Customer*>* inputQueue;
    map<const char*,sem_t*> semaphores;
    map<const int,int*> sharedIntegers;
public:
    PostOffice();
    ~PostOffice();
    bool getInput();
    bool createSemaphore(const char*,int);
    bool createSharedSegment(const int,size_t);
    bool processCustomers(const char*, const char*, const int);
    bool printStatistics(const int);
    bool removeSharedSegment(const int, size_t);
    bool removeSemaphore(const char*);
};

#endif // POSTOFFICE_H
