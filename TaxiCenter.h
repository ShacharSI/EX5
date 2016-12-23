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
#include "Socket.h"
#include <stdexcept>

/**
 * a class that represent a taxi center
 * runs all taxi's
 */
class TaxiCenter {


public:
    void addDriverToCenter(Driver* d);

    TaxiCenter();
    ~TaxiCenter();
    TaxiCenter(Map m);

    bool setTrip(Trip t) ;

    Point giveLocation(int id) throw(invalid_argument) ;

    list <Driver*>& getActiveDriver();

    list <Driver*> getNotActiveDriver();

    void addTrip(Trip t);

    void setActiveDriver(Driver* d);

    void setNotActiveDriver(Driver* d);

    list<Taxi *> getNotActiveTaxis();

    void deleteMap();

    void addTaxi(Taxi *t);

    void moveAll();

private:
    void removeDriver(Driver* d, list <Driver*> l);
    Socket socket;
public:
    void setSocket(const Socket &socket);

private:
    Map map;
    Trip currentTrip;

    void sendTaxiToLocation(Driver* d, Trip t);

    Driver* getClosetTaxi(Point p);

    list<Taxi *> notActiveTaxis;
    list <Driver*> activeDrivers;
    list <Driver*> notActiveDriver;
    queue<Trip> trips;

    void attachTaxiToDriver(Driver* d);

    bool checkTaxiAttachment(Driver* driver);

    void setAllTrips();

    void activateClosest(list <Driver*> list, Driver* driver);
};


#endif //TM_TAXICENTER_H
