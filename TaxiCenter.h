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
    void addDriverToCenter(Driver* d);

    TaxiCenter();
    ~TaxiCenter();
    TaxiCenter(Map m,Socket* s);

    bool sendTrip(Trip t) ;

    Point giveLocation(int id) throw(invalid_argument) ;

    list <Driver*>& getActiveDriver();

    list <Driver*> getNotActiveDriver();

    void addTrip(Trip t);

    void setActiveDriver(Driver* d);

    void setNotActiveDriver(Driver* d);

    list<Taxi *> getNotActiveTaxis();
    void assignTrip(unsigned int time);
    void deleteMap();

    void addTaxi(Taxi *t);

    void moveAll(Socket* s);
    Taxi* assignTaxi(int vehicle_id);
    void setSocket();

private:
    Map map;
    Trip currentTrip;

    void sendTaxiToLocation(Driver* d);

    Driver* getClosetTaxi(Trip p);

    list<Taxi *> notActiveTaxis;
    list <Driver*> activeDrivers;
    list <Driver*> notActiveDriver;
    queue<Trip> trips;
    Socket* socket;

    void attachTaxiToDriver(Driver* d);

    bool checkTaxiAttachment(Driver* driver);

    void setAllTrips();

    void activateClosest(list <Driver*> list, Driver* driver);
};


#endif //TM_TAXICENTER_H
