//
// Created by haim6678 on 09/01/17.
//

#ifndef EX3_TM_THREAD_RUNNER_H
#define EX3_TM_THREAD_RUNNER_H


#include <map>
#include "Driver.h"
#include "TaxiCenter.h"
#include "Tcp.h"
#include "Trip_Info.h"
#include "Mutex_Locker.h"

class Thread_Runner {

public:
    Thread_Runner(TaxiCenter *c);
    void *run(void *);
    Map *getMap() const;
    std::list<Searchable*> checkTrips(Driver* d);
    void *getTrip(void *t);
private:
    list<Trip_Info *> trips;
    Driver *getDriver(Tcp *socket);
    Map *m;
    static Mutex_Locker* mutex;
    TaxiCenter *taxiCenter;
};


#endif //EX3_TM_THREAD_RUNNER_H
