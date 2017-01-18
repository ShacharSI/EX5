//
// Created by haim6678 on 11/01/17.
//

#include "Thread_Manage.h"
#include <stdexcept>

Thread_Manage *Thread_Manage::instance = NULL;
//initializing the mutexes
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
/**
 * @return an instance of the class
 */
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
/**
 * add a queueMessage to the Thread_Manage singelton
 */
void Thread_Manage::addQueueMessage(int d, std::queue<string> *q) {
    Thread_Manage::threadMessagesLocker->lock();
    this->threadMasseges[d] = q;
    Thread_Manage::threadMessagesLocker->unlock();
}

/**
 * add thread and Thread_Class to the thier map
 * @param t pthread_t
 * @param c Thread_Class
 */
void Thread_Manage::addThread(pthread_t t, Thread_Class *c) {
    Thread_Manage::threadInfoLocker->lock();
    this->threadInfo[t] = c;
    Thread_Manage::threadInfoLocker->unlock();
}

/**
 * @param pt pthread_t
 * @return the Thread's Socket Descriptor
 */
int Thread_Manage::getThreadsSocketDescriptor(pthread_t pt) {
    Thread_Manage::descriptorsMapLocker->lock();
    int descriptor = threadInfo[pt]->getThreadsSocketDescriptor();
    Thread_Manage::descriptorsMapLocker->unlock();
    return descriptor;
}
/**
 * adds one message to a match quee
 */
void Thread_Manage::addMessage(int d, string s) {
    this->threadMasseges[d]->push(s);
}

/**
 * @return the list of the pthread
 */
list<pthread_t *> *Thread_Manage::getThreadList() {
    return threadList;
}
/**
 * add a thread to the list of the pthread
 * @param t pointer to pthread_t
 */
void Thread_Manage::addThread(pthread_t *t) {
    Thread_Manage::threadInfoLocker->lock();
    this->threadList->push_back(t);
    Thread_Manage::threadInfoLocker->unlock();
}
/**
 * d-tor
 */
Thread_Manage::~Thread_Manage() {
    delete this->instanceLocker;
    delete this->threadMessagesLocker;
    delete this->threadInfoLocker;
    delete this->threadListLocker;
    delete this->descriptorsMapLocker;


    for (int i = 0; i < this->numDrivers; ++i) {
        delete this->threadMasseges[i];
    }
    delete threadMasseges;
    std::map<pthread_t ,Thread_Class*>::iterator it;

    std::map<pthread_t, Thread_Class *> mymap = this->threadInfo;
    for (it = mymap.begin(); it != mymap.end(); ++it) {
        delete it->second;
    }

}
/**
 * pop one message from the driver's queueMessage
 * @param d driver's Id
 */
void Thread_Manage::popMessage(int d) {
    Thread_Manage::threadMessagesLocker->lock();
    this->threadMasseges[d]->pop();
    Thread_Manage::threadMessagesLocker->unlock();
}

/**
 * @param driverId  a driverId
 * @return a queueMessage according to driverId
 */
queue<string> *Thread_Manage::getThreadsQueue(int driverId) {
    queue<string> **mymap = this->threadMasseges;
    if ((driverId < 0) || (driverId > this->numDrivers)) {
        throw invalid_argument("wrong coordinate");
    }
    return threadMasseges[driverId];

}

/**
 * set Initial MessagesQueues according to the numDrivers
 * @param numDrivers
 */
void Thread_Manage::setInitialMessagesQueues(int numDrivers) {
    queue<string> **s = new queue<string> *[numDrivers];
    this->threadMasseges = s;
    this->numDrivers = numDrivers;
    for (int i = 0; i < numDrivers; i++) {
        std::queue<string> *messageQueue = new queue<string>;
        this->threadMasseges[i] = messageQueue;
    }
}
/**
 * @return the array of the queueMessage
 */
queue<string> **Thread_Manage::getThreadMasseges() {
    return threadMasseges;
}
/**
 * @return the number of Drivers
 */
int Thread_Manage::getNumDrivers() const {
    return numDrivers;
}
/**
 * set the list of the threads
 * @param threadList list of threads
 */
void Thread_Manage::setThreadList(std::list<pthread_t *> *threadList) {
    this->threadList = threadList;
}