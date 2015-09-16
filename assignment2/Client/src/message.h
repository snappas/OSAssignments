//Ryan Wedge
//Assignment 2
//COSC 4330 Spring 2015

#ifndef MESSAGE_H
#define MESSAGE_H
#include <vector>
using namespace std;

class message
{
private:
    int length;
    vector<int> responseMessage;
public:
    message();
    ~message();
    message(int,int,int);
    message(int);
    void setId(int);
    void setCode(int);
    void setValue(int);
    void add(int);
    int* getMessage();
    int getSize();
    void setLength(int);
};

#endif // MESSAGE_H
