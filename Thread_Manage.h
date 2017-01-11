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
    std::map<pthread_t, Thread_Class> threadInfo;
public:
    void addMassage(pthread_t,std::queue<std::string>);
    void addThread(pthread_t,Thread_Class);
    static Thread_Manage* getInstance();
    bool Occupy();
};


#endif //EX3_TM_THREAD_MANAGE_H
