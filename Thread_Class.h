//
// Created by haim6678 on 11/01/17.
//

#ifndef EX3_TM_THREAD_CLASS_H
#define EX3_TM_THREAD_CLASS_H


#include <sys/types.h>
/**
 * class holds the match socketDescriptor
 */
class Thread_Class {

private:
    int socketDescriptor;
public:
    Thread_Class(int SocketDescriptor);
    int getThreadsSocketDescriptor() const;
};


#endif //EX3_TM_THREAD_CLASS_H
