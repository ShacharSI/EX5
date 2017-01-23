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
    static Mutex_Locker* driverLocker;
    ~Thread_Runner();
    static void* runHelper(void* v);
    static void* tripHelper(void* v);
    void *run(void);
    std::list<Searchable*>* checkTrips(Driver* d, int time);
    void *getTrip(void);
    static Thread_Runner* getInstance(TaxiCenter* c,Tcp* t);
    bool Occupy();
    void pushInitialDriver(Driver* d);
    void addTripToCalculate(Trip t);
    bool checkFirstDriver(Driver* d);
    void pushNotActiveDriver(Driver* d);
private:
    Thread_Runner(TaxiCenter *c,Tcp* t){
        this->taxiCenter = c;
        this->m = c->getMap();
        this->tcpSock = t;
        this->notActiveDrivers = new list<Driver*>;
        this->initialList = new list<Driver*>;
    };
    std::queue<Trip> tripsToCalculate;
    bool inUse;

    std::list<Driver*>* initialList;
    static bool created;
    static Thread_Runner* instance;
    list<Trip_Info *> trips;
    list<Driver*>* notActiveDrivers;
    Driver *getDriver();
    Map *m;
    Tcp *tcpSock;
    TaxiCenter *taxiCenter;
    static Mutex_Locker* instanceLocker;
    static Mutex_Locker* tripsLocker;
    static Mutex_Locker* printLocker;
};


#endif //EX3_TM_THREAD_RUNNER_