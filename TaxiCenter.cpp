#include "TaxiCenter.h"
#include "Socket.h"
#include <boost/foreach.hpp>
#include <iostream>
#include "Driver.h"
#include "Udp.h"
#include "Thread_Manage.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/list.hpp>


/**
 * the empty constructor
 */
TaxiCenter::TaxiCenter() {

}

/**
 * the constructor
 */
TaxiCenter::TaxiCenter(Map *mp, Socket *soc) {
    this->map = mp;
    this->socket = soc;
    this->searchAlgo = new Bfs;
}

/**
 * returns the location of a given taxi
 */
Point TaxiCenter::giveLocation(int id) throw(invalid_argument) {
    if(!this->driversLocation[id]){
        Thread_Manage* thread_manage = Thread_Manage::getInstance();
        thread_manage->addMessage(id,"location");
        while(!this->driversLocation[id]);
    }
    return *(this->driversLocation[id]);

    /*int size = this->drivers.size();
    for (int i = 0; i < size; i++) {
        Driver *d = this->drivers.front();
        if (d->getId() == id) {
            return d->getTaxi()->getLocation();
        }
        this->drivers.pop_front();
        this->drivers.push_back(d);
    }*/
}


/**
 * adding a driver to the taxi center
 */
void TaxiCenter::addDriverToCenter(Driver *d) {
    this->drivers.push_back(d);
}


/**
 * getting a vheicle id attaching to driver in our list a taxi
 * and return a taxi for the client driver
 */
Taxi *TaxiCenter::attachTaxiToDriver(int vhecleId) {
    Taxi *t = NULL;
    for (int i = 0; i < this->notActiveTaxis.size(); i++) {
        t = this->notActiveTaxis.back();
        if (t->getCarId() == vhecleId) {
            this->notActiveTaxis.pop_back();
            return t;
        }
        this->notActiveTaxis.pop_back();
        this->notActiveTaxis.push_front(t);
    }
    return NULL;
}

/**
 * @return - the list of taxi's not attached yet to a driver
 */
list<Taxi *> &TaxiCenter::getNotActiveTaxis() {
    return this->notActiveTaxis;
}

/**
 * @param t - adding a taxi to the center
 */
void TaxiCenter::addTaxi(Taxi *t) {
    this->notActiveTaxis.push_back(t);
}

/**
 * moving all the taxis one step
 */
void TaxiCenter::moveAll() {
    char *buffer = (char *) malloc(4096 * sizeof(char));
    //iterate over the drivers
    for (int i = 0; i < this->drivers.size(); i++) {
        Driver *d = this->drivers.front();
        //verify that the driver has where to go
        if (d->getTaxi()->getRouth().size() > 0) {
            //move the driver here
            d->move();
            //send the client go
            string go = "Go";
            //todo send all threads "GO"
        }
        this->drivers.pop_front();
        this->drivers.push_back(d);
    }
    free(buffer);
}


/**
 * the deconstructor
 */
TaxiCenter::~TaxiCenter() {
    long size = this->notActiveTaxis.size();
    for (int i = 0; i < size; i++) {
        Taxi *t = notActiveTaxis.front();
        notActiveTaxis.pop_front();
        delete t;
    }
    size = this->drivers.size();
    for (int i = 0; i < size; i++) {
        Driver *d = drivers.front();
        drivers.pop_front();
        delete d;
    }
    delete this->searchAlgo;
    delete this->map;
}

unsigned int TaxiCenter::getTime() const {
    return time;
}

Map *TaxiCenter::getMap() const {
    return map;
}

list<Driver *> &TaxiCenter::getDrivers() {
    return drivers;
}

void TaxiCenter::setRout(Driver *d, list<Searchable*> l) {
    int size = this->drivers.size();
    for (int i = 0; i <size ; i++) {
        Driver* driver = this->drivers.front();
        if (d->getId()==driver->getId()){
            driver->setRouth(l);
            return;
        }
        this->drivers.pop_front();
        this->drivers.push_back(driver);
    }
}

void TaxiCenter::setLocation(int driverID,Point* p) {
    this->driversLocation[driverID] = p;
}
