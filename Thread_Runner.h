//
// Created by haim6678 on 09/01/17.
//

#ifndef EX3_TM_THREAD_RUNNER_H
#define EX3_TM_THREAD_RUNNER_H


#include <map>
#include "Driver.h"
#include "TaxiCenter.h"

class Thread_Runner {

public:
    Thread_Runner(TaxiCenter *c);

    void *run(void *);


private:
    Driver *d;
    map<Driver *, int> *socketDesMap;
    map<int,std::list<Searchable*>> trips
    void getDriver(Socket* socket);

    void getTrip();

    int numLiveThreads;
    int readByThreads;
    TaxiCenter *taxiCenter;
    string massege;
    Socket sock;
};


#endif //EX3_TM_THREAD_RUNNER_H