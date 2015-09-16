//Ryan Wedge -- COSC 4330 -- Spring 2015

#include "customer.h"
#include <string>

using namespace std;
Customer::Customer(string name, int start, int duration)
{
    customername = name;
    arrival_delay = start;
    service_time = duration;
}

Customer::~Customer()
{
}

int Customer::getArrivalDelay() const{
    return arrival_delay;
}

int Customer::getServiceTime() const{
    return service_time;
}

string Customer::getCustomername() const{
    return customername;
}
