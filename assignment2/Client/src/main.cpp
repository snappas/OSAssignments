//Ryan Wedge
//Assignment 2
//COSC 4330 Spring 2015

#define PORTNUM 50959
#define HOST "127.0.0.1"
#define DETAILED_OUTPUT 0

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "semaphoreclient.h"

int sem_create(int initial_value);
int kill_server();
int sem_P(int sem_id);
int sem_V(int sem_id);
int sem_destroy(int sem_id);

int main() {
    int sem1, mutex; //semaphores
    int pid; // process ID
    if ((sem1 = sem_create(3)) < 0) {
         printf("Cannot create semaphore sem1.\n");
         _exit(1);
    } 
    if ((mutex = sem_create(1)) < 0) {
         _exit(2);
         printf("Cannot create semaphore mutex.\n");
    } 
    // basic checks
    sem_P(sem1);
    sem_P(sem1);
    sem_P(sem1);
    printf("Completed three P() operations on sem1.\n");
    sem_V(sem1);
    sem_V(sem1);
    sem_V(sem1);
    printf("Completed three V() operations on sem1.\n");
    if (sem_P(10) >= 0) {
        printf("Server accepted a call to a non-existent semaphore!\n");
    }
    
    if ((pid = fork()) == 0) {
        // child process
        printf("Child process requests the mutex.\n");
        sem_P(mutex);
        printf("Child process got the mutex.\n");
        sleep(10);
        printf("Child process wants to release the mutex.\n");
        sem_V(mutex);
        printf("Child process released the mutex.\n");
        _exit(0);
    }
    sleep(2);
    printf("Parent process requests the mutex.\n");
    sem_P(mutex);
    printf("Parent process got the mutex.\n");
    sleep(10);
    printf("Parent process wants to release the mutex.\n");
    sem_V(mutex);
    printf("Parent process released the mutex.\n");

    // Ending
    sem_destroy(sem1);
    if (sem_P(sem1) >= 0) {
        printf("Semaphore sem1 was not properly destroyed!\n");
    }
    sem_destroy(mutex);
    if (sem_P(mutex) >= 0) {
        printf("Semaphore mutex was not properly destroyed!\n");
    }
    kill_server();
} // main

int kill_server(){
    semaphoreClient s(HOST,PORTNUM);
    s.setLogging(DETAILED_OUTPUT);
    return s.kill_server();
}
int sem_P(int sem_id){
    semaphoreClient s(HOST,PORTNUM);
    s.setLogging(DETAILED_OUTPUT);
    return s.decrement(sem_id);
}
int sem_V(int sem_id){
    semaphoreClient s(HOST,PORTNUM);
    s.setLogging(DETAILED_OUTPUT);
    return s.increment(sem_id);
}
int sem_destroy(int sem_id){
    semaphoreClient s(HOST,PORTNUM);
    s.setLogging(DETAILED_OUTPUT);
    return s.destroy(sem_id);
}
int sem_create(int initial_value){
    semaphoreClient s(HOST,PORTNUM);
    s.setLogging(DETAILED_OUTPUT);
    return s.create(initial_value);
}


