//
// Created by haim6678 on 11/01/17.
//

#ifndef EX3_TM_MUTEX_LOCKER_H
#define EX3_TM_MUTEX_LOCKER_H


#include <sys/types.h>
/**
 * class holds a pthread_mutex and managing it
 */
class Mutex_Locker {

private:
    pthread_mutex_t mutex;
public:
    void lock();
    void unlock();
    Mutex_Locker();
    ~Mutex_Locker();
};


#endif //EX3_TM_MUTEX_LOCKER_H
