//
// Created by haim6678 on 11/01/17.
//

#include "Thread_Manage.h"

Thread_Manage *Thread_Manage::instance = NULL;
Mutex_Locker *Thread_Manage::instanceLocker = new Mutex_Locker();
Mutex_Locker *Thread_Manage::threadInfoLocker = new Mutex_Locker();
Mutex_Locker *Thread_Manage::threadMessagesLocker = new Mutex_Locker();
Mutex_Locker *Thread_Manage::descriptorsMapLocker = new Mutex_Locker();
Mutex_Locker *Thread_Manage::threadListLocker = new Mutex_Locker();
bool Thread_Manage::created = false;

bool Thread_Manage::Occupy() {
    if (!inUse) {
        this->inUse = true;
        return true;
    }
    return false;
}

Thread_Manage *Thread_Manage::getInstance() {
    if (!Thread_Manage::created) {
        Thread_Manage::instanceLocker->lock();
        if (!Thread_Manage::created) {
            Thread_Manage::instance = new Thread_Manage;
            Thread_Manage::created = true;
        }
        Thread_Manage::instanceLocker->unlock();
    }
    return instance;
}

void Thread_Manage::addQueueMessage(int d, std::queue<string> *q) {
    Thread_Manage::threadMessagesLocker->lock();
    this->threadMasseges[d] = q;
    Thread_Manage::threadMessagesLocker->unlock();
}



void Thread_Manage::addThread(pthread_t t, Thread_Class *c) {
    Thread_Manage::threadInfoLocker->lock();
    this->threadInfo[t] = c;
    Thread_Manage::threadInfoLocker->unlock();
}


int Thread_Manage::getThreadsSocketDescriptor(pthread_t pt) {
    Thread_Manage::descriptorsMapLocker->lock();
    int descriptor = threadInfo[pt]->getThreadsSocketDescriptor();
    Thread_Manage::descriptorsMapLocker->unlock();
    return descriptor;
}

void Thread_Manage::addMessage(int d, string s) {
    this->threadMasseges[d]->push(s);
}

/*void Thread_Manage::addDriver(Driver *d, int sockDes) {
    this->descriptorsMap.insert(std::pair<Driver *, int>(d, sockDes));
}*/

list <pthread_t*>* Thread_Manage::getThreadList() {
    return threadList;
}

void Thread_Manage::addThread(pthread_t* t) {
    Thread_Manage::threadInfoLocker->lock();
    this->threadList->push_back(t);
    Thread_Manage::threadInfoLocker->unlock();
}
//

Thread_Manage::~Thread_Manage() {
     delete this->instanceLocker;
     delete this->threadMessagesLocker;
     delete this->threadInfoLocker;
     delete this->threadListLocker;
     delete this->descriptorsMapLocker;


    for (int i = 0; i <this->numDrivers ; ++i) {
        delete(this->threadMasseges[i]);
    }
    delete(threadMasseges);
    this->threadInfo.clear();
    //delete(Thread_Manage::instance); //todo how to delete this???

}

void Thread_Manage::popMessage(int d) {
    Thread_Manage::threadMessagesLocker->lock();
    this->threadMasseges[d ]->pop();
    Thread_Manage::threadMessagesLocker->unlock();
}


queue<string> *Thread_Manage::getThreadsQueue(int driverId) {
    queue<string> **mymap = this->threadMasseges;
    if ((driverId < 0) || (driverId > this->numDrivers)) {
        return NULL; //todo null or throw exeption?
    }
    return threadMasseges[driverId];

}

void Thread_Manage::setInitialMessagesQueues(int numDrivers) {
    queue<string> **s = new queue<string> *[numDrivers];
    this->threadMasseges = s;
    this->numDrivers = numDrivers;
    for (int i = 0; i < numDrivers; i++) {
        std::queue<string> *messageQueue = new queue<string>;
        this->threadMasseges[i] = messageQueue;
    }
}

queue<string> **Thread_Manage::getThreadMasseges() {
    return threadMasseges;
}

int Thread_Manage::getNumDrivers() const {
    return numDrivers;
}

void Thread_Manage::setThreadList(std::list <pthread_t*> *threadList) {
    this->threadList = threadList;
}
