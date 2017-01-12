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

    static void* runHelper(void* v);
    static void* tripHelper(void* v);
    void *run(void);
    Map *getMap() const;
    std::list<Searchable*> checkTrips(Driver* d);
    void *getTrip(void);
    static Thread_Runner* getInstance(TaxiCenter* c,Tcp* t);
    bool Occupy();
    void addTripToCalculate(Trip t);
private:
    std::queue<Trip> tripsToCalcullate;
    Tcp *tcpSock;
    bool inUse;
    static bool created;
    static Thread_Runner* instance;
    Thread_Runner(TaxiCenter *c,Tcp* t){
        this->taxiCenter = c;
        this->m = c->getMap();
        this->tcpSock = t;
    };
    list<Trip_Info *> trips;
    Driver *getDriver(Tcp *socket);
    Map *m;
    TaxiCenter *taxiCenter;
    static Mutex_Locker* instanceLocker;
    static Mutex_Locker* tripsLocker;
};


#endif //EX3_TM_THREAD_RUNNER_H
