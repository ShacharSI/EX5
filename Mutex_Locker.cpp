//
// Created by haim6678 on 11/01/17.
//

#include <pthread.h>
#include <cstdio>
#include "Mutex_Locker.h"

void Mutex_Locker::lock() {
    pthread_mutex_lock(&this->mutex);
}

void Mutex_Locker::unlock() {
    pthread_mutex_unlock(&this->mutex);
}

Mutex_Locker::Mutex_Locker() {
    if(pthread_mutex_init(&this->mutex,NULL)!=0){
        perror("init lock probelm");
    }
}

Mutex_Locker::~Mutex_Locker() {
    pthread_mutex_destroy(&this->mutex);
}
