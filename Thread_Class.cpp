//
// Created by haim6678 on 11/01/17.
//

#include "Thread_Class.h"
/**
 * @return the socket Descriptor
 */
int Thread_Class::getThreadsSocketDescriptor() const {
    return this->socketDescriptor;
}
/**
 * c-tor
 * @param socketDescriptor
 */
Thread_Class::Thread_Class(int socketDescriptor) {
    this->socketDescriptor = socketDescriptor;
}
