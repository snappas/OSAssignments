//Ryan Wedge
//Assignment 2
//COSC 4330 Spring 2015

#include "semaphoreclient.h"
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include "message.h"
#include <cstdarg>



using namespace std;
semaphoreClient::semaphoreClient()
{
    this->destIP = "";
    this->port = -1;
    this->connectedSocket = -1;
    this->logging = true;
    messageToServer.setLength(3);
    messageFromServer.setLength(1);
}

semaphoreClient::~semaphoreClient()
{
}

semaphoreClient::semaphoreClient(string ip, int p){
    this->destIP = ip;
    this->port = p;
}

//I read about the sockets from multiple sources:
//http://www2.cs.uh.edu/~paris/4330/Sockets.html
//https://www.freebsd.org/doc/en/books/developers-handbook/sockets-essential-functions.html
//http://en.wikibooks.org/wiki/C_Programming/Networking_in_UNIX
int semaphoreClient::connectToServer(){
    int newSocket;
    struct sockaddr_in sockAddress;
    memset(&sockAddress, 0, sizeof(sockAddress));
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_addr.s_addr = inet_addr(this->destIP.c_str());
    sockAddress.sin_port = htons(this->port);
    if((newSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("socket");
        exit(1);
    }else if(connect(newSocket, (struct sockaddr *)&sockAddress, sizeof(sockAddress)) < 0){
        perror("connect");
        close(newSocket);
        exit(2);
    }
    this->connectedSocket = newSocket;
    return newSocket;
}

int semaphoreClient::receiveFromServer(int s, int bytes){
    int n;
    if((n = read(this->connectedSocket,this->reply, bytes)) <= 0){
        if(n < 0){
            perror("read");
            return -1;
        }else{
			//logging message format: s = string, d = digit 
			//sd = string parameter followed by digit parameter
			//ex: loggingMessage("sd",const char*,int&)
            loggingMessage("s","Log: Empty message received"); 
            return -1;
        }
    }
    return this->reply[0];
}

int semaphoreClient::sendToServer(){
    int* response = messageToServer.getMessage();
    loggingMessage("sdsdsds","Log: Sending: [",response[0],", ",response[1],", ",response[2],"]");
    if(write(this->connectedSocket,messageToServer.getMessage(), messageToServer.getSize()) < 0){
        perror("send");
        return -1;
    }else{
        return 0;
    }
}

int semaphoreClient::create(int initial_value){
    int sock, status, reply;
    messageToServer.setValue(initial_value);
    messageToServer.setCode(0);
    if((sock = connectToServer()) > -1){
        if((status = sendToServer()) > -1){
            loggingMessage("s","Log: Sem_Create sent to server ");
            reply = receiveFromServer(sock,4);
            loggingMessage("sd","Log: Sem_Create message from server: ", reply);
            close(sock);
        }
    }
    return reply;
}

int semaphoreClient::decrement(int sem_id){
    int sock, status, reply;
    messageToServer.setCode(1);
    messageToServer.setId(sem_id);
    sock = connectToServer();
    if(sock > -1){
        status = sendToServer();
        if(status > -1){
            loggingMessage("s","Log: Sem_P message sent to server");
            reply = receiveFromServer(sock,4);
            loggingMessage("sd","Log: Sem_P message from server: ",reply);
            close(sock);
        }
    }
    return reply;
}

int semaphoreClient::destroy(int sem_id){
    int sock, status, reply;
    messageToServer.setCode(3);
    messageToServer.setId(sem_id);
    sock = connectToServer();
    if(sock > -1){
        status = sendToServer();
        if(status > -1){
            loggingMessage("s","Log: Sem_Destroy sent to server");
            reply = receiveFromServer(sock,4);
            loggingMessage("sd","Log: Sem Destroy message from server: ", reply);
            close(sock);
        }
    }
    return reply;
}

int semaphoreClient::increment(int sem_id){
    int sock, status, reply;
    messageToServer.setCode(2);
    messageToServer.setId(sem_id);
    sock = connectToServer();
    if(sock > -1){
        status = sendToServer();
        if(status > -1){
            loggingMessage("s","Log: Sem V message sent to server");
            reply = receiveFromServer(sock,4);
            loggingMessage("sd","Log: Sem_V message from server: ", reply);
            close(sock);
        }
    }
    return reply;
}

int semaphoreClient::kill_server(){
    int status, reply;
    messageToServer.setCode(9);
    if(connectToServer() > -1){
        status = sendToServer();
        if(status > -1){
            loggingMessage("s","Log: Message sent to server");
            reply = receiveFromServer(this->connectedSocket,4);
            loggingMessage("sd","Log: Message received from server: ", reply);
            //close(sock); done by server
        }
    }
    return reply;
}

//I found this example of functions that can use an arbitrary number of parameters
//here: http://en.cppreference.com/w/cpp/utility/variadic 
//my logging function is practically the same thing using a boolean to display 
//it conditionally 
void semaphoreClient::loggingMessage(const char* fmt,...){
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

void semaphoreClient::setLogging(bool islogging){
    this->logging = islogging;
}
