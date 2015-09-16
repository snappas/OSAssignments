//Ryan Wedge -- COSC 4330 -- Spring 2015

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>

using namespace std;

class Customer
{
private:
    string customername;
    int arrival_delay;
    int service_time;
public:
    Customer(string,int,int);
    ~Customer();
    string getCustomername() const;
    int getArrivalDelay() const;
    int getServiceTime() const;

};

#endif // CUSTOMER_H
