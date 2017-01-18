//
// Created by haim on 12/27/16.
//

#ifndef DRIVER_MANAGEDRIVER_H
#define DRIVER_MANAGEDRIVER_H


#include "Driver.h"
#include "Tcp.h"

/**
 * a class that runs the driver - the client
 */
class ManageDriver {
private:
    Driver* d;
    Tcp* socket;
    void copyToList(std::list<Searchable*>* list ,std::list<Searchable*>*moveList);
public:
    ManageDriver(string s,Tcp* soc);
    void manage();
    void setTaxi();
    ~ManageDriver();
};


#endif //DRIVER_MANAGEDRIVER_H
