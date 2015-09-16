//Ryan Wedge
//Assignment 2
//COSC 4330 Spring 2015

#include "message.h"
#include <vector>
#include <iostream>
using namespace std;

message::message()
{
    this->responseMessage.reserve(3);
    this->length = 3;
}
message::message(int len){
    this->responseMessage.reserve(len);
    this->length = len;

}

message::~message()
{
}
message::message(int id,int func, int val){
     this->responseMessage.reserve(3);
    this->responseMessage[0] = func;
    this->responseMessage[1] = id;
    this->responseMessage[2] = val;
    this->length = 3;
}

void message::setId(int id){
    this->responseMessage[1] = id;
}
void message::setCode(int func){
    this->responseMessage[0] = func;
}
void message::setValue(int val){
    this->responseMessage[2] = val;
}
int* message::getMessage(){
    return &responseMessage[0];
}
int message::getSize(){
    if(length != -1){
        return (sizeof(int) * length);
    }else{
        return 12;
    }

}

void message::add(int val){
    responseMessage.push_back(val);
}
void message::setLength(int len){
    this->length = len;
    this->responseMessage.reserve(len);
}
