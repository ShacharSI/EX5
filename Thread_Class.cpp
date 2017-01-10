//
// Created by haim6678 on 11/01/17.
//

#include "Thread_Class.h"

pthread_mutex_t *Thread_Class::getPthreadMutex() const {
    return pthreadMutex;
}

int Thread_Class::getThreadsPort() const {
    return threadsPort;
}

Thread_Class::Thread_Class(pthread_mutex_t *t, int port) {
    this->pthreadMutex = t;
    this->threadsPort = port;
}
