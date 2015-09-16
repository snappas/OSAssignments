//Ryan Wedge
//Assignment 2
//COSC 4330 Spring 2015

#ifndef SEMAPHORECLIENT_H
#define SEMAPHORECLIENT_H
#include <string>
#include "message.h"
#define SIZE_OF_RECEIVE 1
using namespace std;

class semaphoreClient
{
private:
    bool logging;
    int reply[SIZE_OF_RECEIVE];
    message messageFromServer;
    message messageToServer;
    string destIP;
    int port;
    int connectedSocket;
    int sendToServer();
    int receiveFromServer(int,int);
    int connectToServer();
    void loggingMessage(const char* fmt, ...);

public:
    semaphoreClient();
    semaphoreClient(string,int);
    ~semaphoreClient();
    int create(int); //sem_create
    int decrement(int); //sem_P
    int increment(int); //sem_V
    int destroy(int); //sem_destroy()
    int kill_server();
    void setLogging(bool);
};


#endif // SEMAPHORECLIENT_H
