//
// Created by haim6678 on 11/01/17.
//

#include "Thread_Manage.h"

Thread_Manage *Thread_Manage::instance = NULL;
Mutex_Locker *Thread_Manage::mutex = new Mutex_Locker();
Thread_Manage::created = false;
bool Thread_Manage::Occupy() {
    if (!inUse) {
        this->inUse = true;
        return true;
    }
    return false;
}

Thread_Manage *Thread_Manage::getInstance() {

    if (!Thread_Manage::created) {
        Thread_Manage::mutex->lock();
        if (!Thread_Manage::created) {
            Thread_Manage::instance = new Thread_Manage;
            Thread_Manage::created = true;
        }
        Thread_Manage::mutex->unlock();
    }
    return instance;
}

void Thread_Manage::addMassage(pthread_t, std::queue<std::string>) {

}

void Thread_Manage::addThread(pthread_t, Thread_Class) {

}
