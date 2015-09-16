//Ryan Wedge
//Assignment 2
//COSC 4330 Spring 2015

#ifndef SEMCONTAINER_H
#define SEMCONTAINER_H
#include <queue>
#define MAX_SEMAPHORES 64
using namespace std;
class SemContainer
{
private:
    int value[MAX_SEMAPHORES];
    queue<int> socketqueue[MAX_SEMAPHORES];
public:
    SemContainer();
    ~SemContainer();
    bool create(int, int&);
    bool increment(int,int&);
    bool decrement(int,int,int&);
    bool destroy(int, int&);
    bool isWaiting(int &);
    queue<int>* getQueue(int&);
    int getValue(int&);

};

#endif // SEMCONTAINER_H
