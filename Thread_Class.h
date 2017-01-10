//
// Created by haim6678 on 11/01/17.
//

#ifndef EX3_TM_THREAD_CLASS_H
#define EX3_TM_THREAD_CLASS_H


#include <sys/types.h>

class Thread_Class {

private:
    pthread_mutex_t* pthreadMutex;
    int threadsPort;
public:
    Thread_Class(pthread_mutex_t* t,int port);
    pthread_mutex_t *getPthreadMutex() const;

    int getThreadsPort() const;
};


#endif //EX3_TM_THREAD_CLASS_H
