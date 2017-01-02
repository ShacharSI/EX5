//
// Created by haim on 12/27/16.
//

#ifndef DRIVER_MANAGEDRIVER_H
#define DRIVER_MANAGEDRIVER_H


#include "Driver.h"
#include "Socket.h"

class ManageDriver {
private:
    Driver* d;
    Socket* socket;
public:
    ManageDriver(string s,Socket* soc);
    void manage();
    void setTaxi();
    ~ManageDriver();
};


#endif //DRIVER_MANAGEDRIVER_H
