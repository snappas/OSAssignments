//Ryan Wedge
//Assignment 2
//COSC 4330 Spring 2015

#include "semcontainer.h"
#include <iostream>
#include <queue>
#include <sys/socket.h>
#include <error.h>
#include <errno.h>
#include <cstdio>
#include <unistd.h>
using namespace std;

SemContainer::SemContainer()
{
    for(int i = 0;i<MAX_SEMAPHORES;i++){
        value[i] = -1;
    }
}

SemContainer::~SemContainer()
{

}

bool SemContainer::create(int initialval, int &reply){
    for(int i = 0; i<MAX_SEMAPHORES;i++){
        if(value[i] == -1){
            value[i] = initialval;
            reply = i;
            return true;
        }
    }
    reply = -1;
    return false;
}

bool SemContainer::increment(int i,int& reply){
    if(value[i] > -1){
        value[i] += 1;
        reply = 0;
        return true;
    }else{
        reply = -1;
        return true;
    }
}

bool SemContainer::decrement(int i,int s, int & reply){
    if(value[i] > -1){
        if(value[i] == 0){
                socketqueue[i].push(s);
                reply = -2;
                return false;
        }else{
            value[i] -= 1;
            reply = 0;
            return true;
        }
    }else{
        reply = -1;
        return true;
    }
    return false;
}

bool SemContainer::destroy(int i, int& reply){
    if(value[i] != -1){
        value[i] = -1;
        reply = 0;
        if(isWaiting(i)){
            while(isWaiting(i)){
                socketqueue[i].pop();
            }
        }
        return true;
    }else{
        reply = -1;
        return false;
    }
}

bool SemContainer::isWaiting(int& i){
    return !socketqueue[i].empty();
}

queue<int>* SemContainer::getQueue(int& i){
    return &socketqueue[i];
}
int SemContainer::getValue(int& i){
    return value[i];
}
