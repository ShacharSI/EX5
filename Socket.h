//
// Created by haim on 12/22/16.
//

#ifndef EX3_TM_SOCKET_H
#define EX3_TM_SOCKET_H


class Socket {

    virtual int sendInfo() = 0;

    virtual int getInfo() = 0;

    virtual void closeSocket() =0;

    virtual ~Socket() = 0;
};


#endif //EX3_TM_SOCKET_H
