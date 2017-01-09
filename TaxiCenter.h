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
    TaxiCenter(Map* m,Socket* s);

    list<Searchable*> sendTrip(Trip t,Driver* d) ;

    Point giveLocation(int id) throw(invalid_argument) ;

    list <Driver*>* getActiveDriver();

    list <Driver*>* getNotActiveDriver();

    void addTrip(Trip t);

    void setActiveDriver(Driver* d);

    void setNotActiveDriver(Driver* d);

    list<Taxi *>* getNotActiveTaxis();

    void assignTrip(unsigned int time);

    void addTaxi(Taxi *t);

    void moveAll();

    Taxi* attachTaxiToDriver(int vhecleId);
    queue<Trip>* getTrips();
private:
    unsigned int time;
public:
    unsigned int getTime() const;


private:
    Map* map;
    Trip currentTrip;
    Algorithm *searchAlgo;
    void sendTaxiToLocation(Driver* d);

    list<Searchable*> getClosetTaxi(Trip p,Driver* d);
    list<Searchable*> calculateDriverRoute(Point startP, Point endP);

    list<Taxi *>* notActiveTaxis;
    queue<Trip>* trips;
    Socket* socket;
};


#endif //TM_TAXICENTER_H
