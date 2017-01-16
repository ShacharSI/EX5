//
// Created by haim on 11/27/16.
//

#ifndef TM_TAXICENTER_H
#define TM_TAXICENTER_H


#include <vector>
#include "Taxi.h"
#include "Trip.h"
#include "Map.h"
#include "Driver.h"
#include "Bfs.h"
#include "Udp.h"
#include <stdexcept>


/**
 * a class that represent a taxi center
 * runs all taxi's
 */
class TaxiCenter {

public:

    TaxiCenter();

    ~TaxiCenter();

    TaxiCenter(Map *m);

    list<Taxi *> &getNotActiveTaxis();

    void addTaxi(Taxi *t);

    void moveAll();

    Taxi *attachTaxiToDriver(int vhecleId);

    unsigned int getTime() const;

    Map *getMap() const;



private:
    unsigned int time;
    Map *map;
    Algorithm *searchAlgo;
    list<Taxi *> notActiveTaxis;
};


#endif //TM_TAXICENTER_H
