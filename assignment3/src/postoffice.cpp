//Ryan Wedge -- COSC 4330 -- Spring 2015

#include "postoffice.h"
#include "customer.h"
#include <sstream>
#include <string>
#include <queue>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

PostOffice::PostOffice()
{
    numServiced = 0;
}

PostOffice::~PostOffice()
{
}

bool PostOffice::getInput(){
    string input; // to store stdin input
    inputQueue = new queue<Customer*>();
    while(getline(cin, input)){ // get line of input from stdin as string
        istringstream iss(input);
        string customer_name = "";
        int arrival_delay = 0;
        int service_time = 0;
        iss >> customer_name >> arrival_delay >> service_time; //parse input string
        inputQueue->push(new Customer(customer_name,arrival_delay,service_time)); // store as Customer object
    }
    if(inputQueue->size() == 0){
        cout << "Error: No input" << endl;
        exit(2);
    }
    return true;
}

bool PostOffice::createSemaphore(const char* name,int initial_value){
    // Create post office semaphore with initial value set to number of clerks
    sem_t* semaddr;
    semaddr = sem_open(name, O_CREAT, 0600, initial_value);
    if (semaddr == SEM_FAILED) {
        perror("Unable to create clerks semaphore");
        sem_unlink(name);
        exit(1);
    }else{
        semaphores[name] = semaddr;
    }
    int semvalue = 0;
    // get and display value of new semaphore
    sem_getvalue(semaphores[name], &semvalue);
    cout << "The initial value of semaphore: " << name << " is "<< semvalue << endl;
    return true;
}

bool PostOffice::createSharedSegment(const int key_mem, size_t memsize){
    // request new shared memory size of integer
    int sid_mem;
    sid_mem = shmget(key_mem, memsize, 0600 | IPC_CREAT);
    if (sid_mem == -1) {
        perror("Cannot get shared segment");
        exit(3);
    }else{
        // assign shared memory to integer pointer
        int* sharedInt;
        sharedInt = (int *) shmat(sid_mem, NULL, 0);
        if (sharedInt == NULL) {
            perror("Cannot get address of shared segment");
            exit(24);
        }else{
            *sharedInt = 0; //initialize shared memory to 0
            sharedIntegers[key_mem] = sharedInt;
        }
    }
    return true;
}

bool PostOffice::processCustomers(const char* clerks, const char* mutex, const int key_mem){
    // process the input
    while(!inputQueue->empty()){
        Customer* inputCustomer = inputQueue->front(); // get first customer
        sleep(inputCustomer->getArrivalDelay());
        int pid;
        pid = fork();
        if (pid == 0) { //service the customer in the child process
            cout << inputCustomer->getCustomername() << " arrived at the post office" << endl;
            //check to see if clerks are available
            int semvalue;
            sem_getvalue(semaphores[clerks], &semvalue);
            if(semvalue == 0){
                //customer has to wait
                //cout << inputCustomer->getCustomername() << " has to wait" << endl;
                sem_wait(semaphores[mutex]); // request shared memory
                *(sharedIntegers[key_mem]) += 1;
                sem_post(semaphores[mutex]); // finished with shared memory
            }
            // use a clerk
            sem_wait(semaphores[clerks]); // request a clerk
            cout << inputCustomer->getCustomername() << " starts being helped" << endl;
            sleep(inputCustomer->getServiceTime());
            cout << inputCustomer->getCustomername() << " left the post office" << endl;
            sem_post(semaphores[clerks]); // finished with clerk
            _exit(0); // terminate child process
        }
        inputQueue->pop(); // remove customer from parent process
    }
    while(wait(0) != -1){ //wait until all children have terminated
        numServiced += 1; // count each terminated child process as a serviced customer
    }
    return true;
}

bool PostOffice::printStatistics(const int key_mem){
    cout << endl;
    cout << "Customers serviced: " << numServiced << "\n";
    cout << "Customers that did not have to wait: " << numServiced - *sharedIntegers[key_mem] << "\n";
    cout << "Customers that had to wait: " << *sharedIntegers[key_mem] << "\n";
    cout << endl;
    return true;
}

bool PostOffice::removeSharedSegment(const int key_mem, size_t memsize){
    // We detach the shared memory segment before destroying it
    shmdt(sharedIntegers[key_mem]);
    int sid_mem;
    sid_mem = shmget(key_mem, memsize, 0600);
    shmctl(sid_mem, IPC_RMID, 0);
    return true;
}

bool PostOffice::removeSemaphore(const char* name){
    sem_close(semaphores[name]);
    if(sem_unlink(name) != 0) {
        cout << "WARNING: semaphore " << name << " was not deleted" << endl;
    } // if
    return true;
}
