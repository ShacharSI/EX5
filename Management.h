
#ifndef TM_MANAGEMENT_H
#define TM_MANAGEMENT_H


#include "TaxiCenter.h"
#include <stdexcept>
#include <sstream>
#include "Logic.h"
#include "Thread_Runner.h"

/**
 * a class that manage the all program
 * olding a taxiCenter logic and all the other classes
 */
class Management {
private:
    //unsigned int clock;
    Logic lg;
    TaxiCenter* taxiCenter;
    void setLogicAndMap();
    vector<int> getSizes();
    Socket* socket;
    Thread_Runner* thread_runner;
    int serverPort;

public:
    ~Management();
    unsigned int getTime();
    void assignTrip();
    void setClock();
    void getObstacles();
    void getMap();
    Management(Socket* s);
    void manage();
    Taxi* parseTaxi(string s);
    void parseDriver();
    void parseTrip(string s);
    Point parseLocation(int id);
};


#endif //TM_MANAGEMENT_H