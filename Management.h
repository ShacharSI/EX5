
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
    Logic lg;
    TaxiCenter taxiCenter;
    void setLogicAndMap();
    vector<int> getSizes();

public:
    void getObstacles();
    void getMap();
    Management();
    void manage();
    Taxi* parseTaxi(string s);
    Driver* parseDriver(string s);
    Trip parseTrip(string s);
    Point parseLocation(int id);
};


#endif //TM_MANAGEMENT_H