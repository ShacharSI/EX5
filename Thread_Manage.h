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
    static Thread_Manage* instance;
    static bool created;
    map<pthread_t ,std::queue<std::string>*> threadMasseges;
    map<pthread_t ,Driver*> threadDrivers;
    std::map<pthread_t, Thread_Class*> threadInfo;
    map<Driver*, int> descriptorsMap;
    list<pthread_t> threadList;
    static Mutex_Locker* threadInfoLocker;
    static Mutex_Locker* instanceLocker;
    static Mutex_Locker* threadMessagesLocker;
    static Mutex_Locker* descriptorsMapLocker;
    static Mutex_Locker* threadListLocker;
public:
    map<pthread_t, Driver *> &getThreadDrivers() ;
    map<pthread_t, queue<string>*> &getThreadMasseges();
    ~Thread_Manage();
    list <pthread_t> &getThreadList() ;
    void addThread(pthread_t t);
    queue<string>* getThreadsQueue(pthread_t t);
    void addDriver(Driver* d,int sockDes);
    //map<pthread_t,queue<string>> getThreadMasseges() ;
    void addQueueMessage(pthread_t t, std::queue<std::string>* q);
    void addDriverAndPthread(pthread_t t, Driver* d);
    void addMessage(pthread_t ,string s);
    void addThread(pthread_t t,Thread_Class* c);
    static Thread_Manage* getInstance();
    bool Occupy();
    void popMessage(pthread_t d);
    int getThreadsSocketDescriptor(pthread_t pt);
};


#endif //EX3_TM_THREAD_MANAGE_H
