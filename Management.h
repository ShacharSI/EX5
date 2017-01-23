
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
    int setLogicAndMap();
    vector<int> getSizes();
    Tcp* socket;
    Map* m;
    int serverPort;

public:
    ~Management();
    int getObstacles();
    int getMap();
    Management(Tcp* s);
    void manage();
    Driver* getDriver();
    Taxi* parseTaxi(string s);
    void parseDriver();
    void parseTrip(string s);
    void parseLocation(int id);
};


#endif //TM_MANAGEMENT_H