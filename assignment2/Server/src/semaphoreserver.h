//Ryan Wedge
//Assignment 2
//COSC 4330 Spring 2015

#ifndef SEMAPHORESERVER_H
#define SEMAPHORESERVER_H
#include "semcontainer.h"

class semaphoreServer
{
private:
    enum {SEM_CREATE=0,SEM_P=1,SEM_V=2,SEM_DESTROY=3,KILL_SERVER=9};
    bool logging;
    SemContainer sc;
    int listenSocket;
    int acceptedSocket;
    int getListenSocket(unsigned short);
    bool sendReply(int&,int&);
    int sem_create(int&, int&);
    int sem_P(int&,int&);
    int sem_V(int&,int&);
    int sem_delete(int&,int&);
    int kill_server(int&,int&);
    void loggingMessage(const char* fmt, ...);
public:
    semaphoreServer();
    ~semaphoreServer();
    void listenOnPort(unsigned short);
    void acceptSemaphoreRequests();
    void setLogging(bool);
};

#endif // SEMAPHORESERVER_H
