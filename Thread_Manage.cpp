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

void Thread_Manage::addQueueMessage(pthread_t d, std::queue<string>* q) {
    Thread_Manage::threadMessagesLocker->lock();
    this->threadMasseges[d] = q;
    Thread_Manage::threadMessagesLocker->unlock();
}
void Thread_Manage::addDriverAndPthread(pthread_t t, Driver *d) {
//todo add locker!!!
    this->threadDrivers[t] = d;
}

void Thread_Manage::addThread(pthread_t t, Thread_Class* c) {
    Thread_Manage::threadInfoLocker->lock();
    this->threadInfo[t] = c;
    Thread_Manage::threadInfoLocker->unlock();
}


int Thread_Manage::getThreadsSocketDescriptor(pthread_t pt)  {
    Thread_Manage::descriptorsMapLocker->lock();
    int descriptor = threadInfo[pt]->getThreadsSocketDescriptor();
    Thread_Manage::descriptorsMapLocker->unlock();
    return descriptor;
}

void Thread_Manage::addMessage(pthread_t d, string s) {
    this->threadMasseges[d]->push(s);
}

void Thread_Manage::addDriver(Driver *d, int sockDes) {
    this->descriptorsMap.insert(std::pair<Driver *, int>(d, sockDes));
}

 list <pthread_t> &Thread_Manage::getThreadList()  {
    return threadList;
}

void Thread_Manage::addThread(pthread_t t) {
    Thread_Manage::threadInfoLocker->lock();
    this->threadList.push_back(t);
    Thread_Manage::threadInfoLocker->unlock();
}

Thread_Manage::~Thread_Manage() {
    delete this->instanceLocker;
    delete this->threadMessagesLocker;
    delete this->threadInfoLocker;
    delete this->threadListLocker;
    delete this->descriptorsMapLocker;

    delete instance;

    for (std::map<pthread_t , queue<std::string>*>::iterator it = threadMasseges.begin();
         it != threadMasseges.end(); ++it) {
        //delete it->first;
//        delete it->second;
    }
    for (std::map<pthread_t , Thread_Class*>::iterator it = threadInfo.begin();
         it != threadInfo.end(); ++it) {
        delete it->second;
    }
}

void Thread_Manage::popMessage(pthread_t d) {
    Thread_Manage::threadMessagesLocker->lock();
    this->threadMasseges[d]->pop();
    Thread_Manage::threadMessagesLocker->unlock();
}

map<pthread_t, queue<string>*> &Thread_Manage::getThreadMasseges(){
    return threadMasseges;
}//

map<pthread_t, Driver *> &Thread_Manage::getThreadDrivers()  {
    return threadDrivers;
}

queue<string> *Thread_Manage::getThreadsQueue(pthread_t t) {
    map<pthread_t, queue<string>*> mymap = this->threadMasseges;
    for (std::map<pthread_t, queue<string>*>::iterator it = mymap.begin();
         it != mymap.end(); ++it) {
        if(it->first == t ){
            return it->second;
        }
    }
    return NULL;
}

