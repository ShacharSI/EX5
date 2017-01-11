//
// Created by haim6678 on 11/01/17.
//

#ifndef EX3_TM_THREAD_MANAGE_H
#define EX3_TM_THREAD_MANAGE_H


#include <sys/types.h>
#include <map>
#include <queue>
#include "Thread_Class.h"
#include "Searchable.h"
#include "Mutex_Locker.h"

class Thread_Manage {

private:
    bool inUse;
    static Mutex_Locker* mutex;
    static Thread_Manage* instance;
    static bool created;
    std::map<pthread_t, std::queue<std::string>> threadMasseges;
public:
    map<pthread_t, queue<string>> &getThreadMasseges() ;

    map<pthread_t, Thread_Class> &getThreadInfo() ;

private:
    std::map<pthread_t, Thread_Class> threadInfo;
public:
    void addMassage(pthread_t t,std::queue<std::string> q);
    void addThread(pthread_t,Thread_Class );
    static Thread_Manage* getInstance();
    bool Occupy();
};


#endif //EX3_TM_THREAD_MANAGE_H
