//
// Created by sha on 1/23/17.
//

#ifndef EX3_TM_THREADPOOL_H
#define EX3_TM_THREADPOOL_H


#include <vector>
#include <deque>
#include <sys/types.h>
#include "Task.h"

class ThreadPool {
public:
    ThreadPool(int pool_size);
    ~ThreadPool();void *execute_thread();
    int add_task(Task *task);
private:
    int m_pool_size;
    std::vector <pthread_t> m_threads;
    std::deque<Task *> m_tasks;
};


#endif //EX3_TM_THREADPOOL_H
