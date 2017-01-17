//
// Created by haim6678 on 11/01/17.
//

#include <pthread.h>
#include <cstdio>
#include "Mutex_Locker.h"

/**
 * lock the mutex
 */
void Mutex_Locker::lock() {
    pthread_mutex_lock(&this->mutex);
}
/**
 * unlock the mutex
 */
void Mutex_Locker::unlock() {
    pthread_mutex_unlock(&this->mutex);
}
/**
 * c-tor
 * initializing a pthread_mutex
 */
Mutex_Locker::Mutex_Locker() {
    if(pthread_mutex_init(&this->mutex,NULL)!=0){
        perror("init lock probelm");
    }
}

/**
 * d-tor
 * destroying the pthread_mutex
 */
Mutex_Locker::~Mutex_Locker() {
    pthread_mutex_destroy(&this->mutex);
}
