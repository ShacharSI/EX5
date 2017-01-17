#ifndef EX3_TM_THREAD_RUNNER_H
#define EX3_TM_THREAD_RUNNER_H


#include <map>
#include "Driver.h"
#include "TaxiCenter.h"
#include "Tcp.h"
#include "Trip_Info.h"
#include "Mutex_Locker.h"
/**
 * class hold all the  func that the threads use
 * calculates bfs and communicates with the client
 */
class Thread_Runner {

public:
    ~Thread_Runner();
    static void* runHelper(void* v);
    static void* tripHelper(void* v);
    void *run(void);
    std::list<Searchable*>* checkTrips(Driver* d, int time);
    void *getTrip(void);
    static Thread_Runner* getInstance(TaxiCenter* c,Tcp* t);
    bool Occupy();
    void addTripToCalculate(Trip t);

private:
    std::queue<Trip> tripsToCalculate;
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
    Driver *getDriver();//
    Map *m;
    TaxiCenter *taxiCenter;
    static Mutex_Locker* instanceLocker;
    static Mutex_Locker* tripsLocker;
    static Mutex_Locker* driverLocker;
    static Mutex_Locker* timeLocker;
};


#endif //EX3_TM_THREAD_RUNNER_