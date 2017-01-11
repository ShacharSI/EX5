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
#include "Udp.h"
#include "Socket.h"
#include <stdexcept>


/**
 * a class that represent a taxi center
 * runs all taxi's
 */
class TaxiCenter {


public:
    void addDriverToCenter(Driver *d);

    TaxiCenter();

    ~TaxiCenter();

    TaxiCenter(Map *m, Socket *s);

    Point giveLocation(int id) throw(invalid_argument);

    list<Taxi *> &getNotActiveTaxis();

    void addTaxi(Taxi *t);

    void moveAll();

    void setRout(Driver* d,list<Searchable*> l);

    Taxi *attachTaxiToDriver(int vhecleId);

    //
    unsigned int getTime() const;

    list<Driver *> &getDrivers();

    Map *getMap() const;

private:
    unsigned int time;
    Map *map;
    Algorithm *searchAlgo;
    list<Taxi *> notActiveTaxis;
    list<Driver *> drivers;
    queue<Trip> trips;
    Socket *socket;
};


#endif //TM_TAXICENTER_H
