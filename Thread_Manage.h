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
#include "Driver.h"

using namespace std;

class Thread_Manage {

private:
    bool inUse;
    static Mutex_Locker* mutex;
    static Thread_Manage* instance;
    static bool created;
    //map<pthread_t, queue<std::string>> threadMasseges;
    map<Driver*, queue<std::string>> threadMasseges;
    std::map<pthread_t, Thread_Class*> threadInfo;
    map<Driver*, int> driversAndDescriptors;
    list<pthread_t> threadList;
public:
    ~Thread_Manage();
    list <pthread_t> &getThreadList() ;
    void addThread(pthread_t t);
    void addDriver(Driver* d,int sockDes);
    map<Driver*, queue<string>> &getThreadMasseges() ;
    void addQueueMessage(pthread_t t, std::queue<std::string> q);
    void addMessage(Driver* d,string s);
    void addThread(pthread_t t,Thread_Class* c);
    static Thread_Manage* getInstance();
    bool Occupy();
    Thread_Class *getThreadClass(pthread_t pt);
};


#endif //EX3_TM_THREAD_MANAGE_H
