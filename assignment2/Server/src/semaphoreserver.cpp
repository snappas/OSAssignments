//Ryan Wedge
//Assignment 2
//COSC 4330 Spring 2015

#include "semaphoreserver.h"
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <cstdarg>

#define LISTEN_BACKLOG 32

semaphoreServer::semaphoreServer()
{
    this->logging = true;
}

semaphoreServer::~semaphoreServer()
{
}

void semaphoreServer::listenOnPort(unsigned short portnumber){
    getListenSocket(portnumber);
    if(this->listenSocket < 0){
        perror("listen");
        exit(1);
    }
}
int semaphoreServer::getListenSocket(unsigned short portnum){
    struct sockaddr_in host;
    memset(&host, 0, sizeof(host)); //clear host object
    host.sin_family = AF_INET; //type of connection = tcp/ip
    host.sin_addr.s_addr = htonl(INADDR_ANY); //address = any interface
    host.sin_port = htons(portnum); //set port

    if((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
        exit(2);
        return -1;
    }
    if(bind(listenSocket, (struct sockaddr *)&host, sizeof(host)) == -1){
        perror("bind");
        close(listenSocket);
        exit(3);
    }
    if(listen(listenSocket,LISTEN_BACKLOG) == -1){
        perror("listen");
        close(listenSocket);
        exit(4);
    }else{
        cout << "Listening on ";
        unsigned int hostsize = sizeof(host);
        if(getsockname(listenSocket, (struct sockaddr *)&host, &hostsize) == -1){
            perror("getsockname");
            close(listenSocket);
        }else{
            cout << "Port: " << ntohs(host.sin_port) << endl;
        }
    }
    return listenSocket;
}


bool semaphoreServer::sendReply(int &s, int &reply){
    int buffer[1];
    buffer[0] = reply;
    if(write(s, buffer,4) < 0){
        perror("send");
        return false;
    }
    loggingMessage("sdsd","Log-N: Sent: [",reply,"] to Socket:",s);
    return true;
}

void semaphoreServer::acceptSemaphoreRequests(){
    struct sockaddr_in clientAddress;
    socklen_t len = sizeof(clientAddress);
    int data[3];
    int n;

    if((acceptedSocket = accept(listenSocket,(struct sockaddr *)&clientAddress,&len)) < 0){
        if(errno == EINTR){
            return;
        }
        perror("accept");
        _exit(5);
    }else{
        if((n = read(acceptedSocket, data, 12)) <= 0){
            if(n<0){
                perror("recv");
            }else{
                loggingMessage("s","Log-N: Empty message received");
            }
        }else if(n==12){

            loggingMessage("sdsdsdsd","Log-N: Received [",data[0],"][",data[1],"][",data[2],"] from Socket:",acceptedSocket);
            switch(data[0]){
            case SEM_CREATE:
                sem_create(acceptedSocket,data[2]);
                break;
            case SEM_P:
                sem_P(acceptedSocket,data[1]);
                break;
            case SEM_V:
                sem_V(acceptedSocket,data[1]);
                break;
            case SEM_DESTROY:
                sem_delete(acceptedSocket,data[1]);
                break;
            case KILL_SERVER:
                kill_server(acceptedSocket,listenSocket);
                break;
            default:
                loggingMessage("s","Log-N: Invalid function code!");
                close(acceptedSocket);
            }
        }else if(n<12){
            loggingMessage("s","Log-N: Not enough bytes received");
        }else{
            loggingMessage("s","Log-N: Too many bytes received");
        }
    }
}

int semaphoreServer::kill_server(int& s,int& listen){
    loggingMessage("s","Log-S: Kill_Server() operation");
    int reply = 0;
    sendReply(s,reply);
    close(s);
    close(listen);
    exit(0);
    return 0;
}


int semaphoreServer::sem_create(int& s, int& val){
    loggingMessage("s","Log-S: Create() operation");
    int reply;
    sc.create(val,reply);
    if(reply >= 0){
        loggingMessage("sdsd","Log-S: Created semaphore id:",reply,"with value:",sc.getValue(reply));
    }else{
        loggingMessage("s","Log-S: Could not create semaphore");
    }
    sendReply(s,reply);
    close(s);
    return 1;
}

int semaphoreServer::sem_P(int& s, int& id){
    loggingMessage("s","Log-S: P() operation");
    int reply;
    if(sc.decrement(id,s,reply)){
        if(reply >= 0){
            loggingMessage("sdsd","Log-S: Applied P() to id:",id,"value: ",sc.getValue(id));
        }else{
            loggingMessage("sds","Log-S: P() error: semaphore id:",id,"does not exist");
        }
        sendReply(s,reply);
        close(s);
    }else{
        loggingMessage("sdsds","Log-S: Added Socket",s,"to semaphore id:",id,"queue");
    }
    return 1;
}

int semaphoreServer::sem_V(int& s, int& id){
    loggingMessage("s","Log-S: V() operation");
    int reply;
    if(sc.isWaiting(id)){
        reply = 0;
	sendReply(s,reply);
        loggingMessage("sdsd","Log-S: Applied V() & P() to id:",id,"value: ",sc.getValue(id));
        sendReply(sc.getQueue(id)->front(),reply);
        loggingMessage("sdsds","Log-S: Socket:",sc.getQueue(id)->front(),"removed from semaphore id:",id,"queue");
        sc.getQueue(id)->pop();
        
    }else{
        sc.increment(id,reply);
        if(reply >=0){
            loggingMessage("sdsd","Log-S: Applied V() to id:",id,"value: ",sc.getValue(id));
        }else{
            loggingMessage("sds","Log-S: V() error: semaphore id:",id,"does not exist");
        }
        sendReply(s,reply);
        close(s);
    }
    return 1;
}

int semaphoreServer::sem_delete(int& s, int& id){
    loggingMessage("s","Log-S: Destroy() operation");
    int reply;
    sc.destroy(id,reply);
    if(reply >=0){
        loggingMessage("sd","Log-S: Destroyed semaphore id:",id);
    }else{
        loggingMessage("sds","Log-S: Destroy error: semaphore id:",id,"does not exist");
    }
    sendReply(s,reply);
    close(s);
    return 1;
}

void semaphoreServer::setLogging(bool log){
    this->logging = log;
}

//I found this example of functions that can use an arbitrary number of parameters
//here: http://en.cppreference.com/w/cpp/utility/variadic 
//my logging function is practically the same thing using a boolean to display 
//it conditionally 
void semaphoreServer::loggingMessage(const char* fmt,...){
    if(this->logging){
        va_list args;
        va_start(args, fmt);
        while(*fmt != '\0'){
            if(*fmt == 's'){
                char* str = va_arg(args, char *);
                cout << str << " ";
            }else if(*fmt == 'd'){
                int num = va_arg(args, int);
                cout << num << " ";
            }
            ++fmt;
        }
        cout << endl;
        va_end(args);
    }
}

