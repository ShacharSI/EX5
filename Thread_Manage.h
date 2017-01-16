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
    //
    bool inUse;
    static Thread_Manage* instance;
    static bool created;
    int numDrivers;
    queue<string>** threadMasseges;
    map<pthread_t, Thread_Class*> threadInfo;
    list<pthread_t*>* threadList;
    static Mutex_Locker* threadInfoLocker;
    static Mutex_Locker* instanceLocker;
    static Mutex_Locker* threadMessagesLocker;
    static Mutex_Locker* descriptorsMapLocker;
    static Mutex_Locker* threadListLocker;

public:
    void setThreadList(list <pthread_t*> *threadList);
    int getNumDrivers() const;
    ~Thread_Manage();
    static Thread_Manage* getInstance();
    queue<string> **getThreadMasseges() ;
    list <pthread_t*> *getThreadList() ;
    void setInitialMessagesQueues(int numOfDrivers);
    queue<string>* getThreadsQueue(int t);
    void addThread(pthread_t* t);
    //void addDriver(Driver* d,int sockDes);
    void addQueueMessage(int t, std::queue<std::string>* q);
    void addDriverAndPthread(pthread_t t, Driver* d);
    void addMessage(int ,string s);
    void addThread(pthread_t t,Thread_Class* c);
    void popMessage(int d);
    int getThreadsSocketDescriptor(pthread_t pt);
    bool Occupy();
};


#endif //EX3_TM_THREAD_MANAGE_H
