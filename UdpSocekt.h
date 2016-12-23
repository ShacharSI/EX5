//
// Created by haim on 12/22/16.
//

#ifndef EX3_TM_UDPSOCEKT_H
#define EX3_TM_UDPSOCEKT_H


#include "Socket.h"

class UdpSocekt: public Socket {

public:
    UdpSocekt();

    int sendInfo() ;

    int getInfo() ;

    void closeSocket();

    ~Socket();

};


#endif //EX3_TM_UDPSOCEKT_H
