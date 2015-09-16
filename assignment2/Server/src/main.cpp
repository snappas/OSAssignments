//Ryan Wedge
//Assignment 2
//COSC 4330 Spring 2015

#define PORTNUM 50959
#define DETAILED_OUTPUT 1

#include "semaphoreserver.h"

int main()
{
    semaphoreServer server;
    server.setLogging(DETAILED_OUTPUT);
    server.listenOnPort(PORTNUM);
    for(;;){
        server.acceptSemaphoreRequests();
    }
    return 0;
}




