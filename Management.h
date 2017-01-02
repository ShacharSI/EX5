
#ifndef TM_MANAGEMENT_H
#define TM_MANAGEMENT_H


#include "TaxiCenter.h"
#include <stdexcept>
#include <sstream>
#include "Logic.h"
#include "StndTaxiFactory.h"

/**
 * a class that manage the all program
 * olding a taxiCenter logic and all the other classes
 */
class Management {
private:
    unsigned int clock;
    Logic lg;
    TaxiCenter* taxiCenter;
    void setLogicAndMap();
    vector<int> getSizes();
    Socket* socket;

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
    Trip parseTrip(string s);
    Point parseLocation(int id);
};


#endif //TM_MANAGEMENT_H