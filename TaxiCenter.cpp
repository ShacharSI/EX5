#include "TaxiCenter.h"
#include "Socket.h"
#include <boost/foreach.hpp>

/**
 * getting a call from a client
 * if there is no free driver return false
 */
bool TaxiCenter::sendTrip(Trip t) {
    this->currentTrip = t;
    if (this->notActiveDriver.size() > 0) {
        Driver *d = this->getClosetTaxi(t);
        if (d != NULL) {
            this->sendTaxiToLocation(d);
            return true;
        }
    } else {
        return false;
    }

}

Driver *TaxiCenter::getClosetTaxi(Trip t) {
    Driver *closest = NULL;
    std::list<Searchable *> routh;
    if (this->notActiveDriver.size() == 0) {
        return NULL;
    }

    Point start = t.getStartP();
    if (this->notActiveDriver.size() > 0) {
        closest = this->notActiveDriver.front();
        routh = closest->calculateBfs(closest->getLocation(), start);
        std::list<Searchable *> route2 = closest->calculateBfs(t.getStartP(), t.getEndP());
        BOOST_FOREACH(auto &listElement, route2) {
                        routh.push_back(listElement);
                    }
        closest->setRouth(routh);
    }
    return closest;
}

void TaxiCenter::sendTaxiToLocation(Driver *d) {
    /**
     * if the driver is in the taxi center then attach him a taxi and send him
     * if he is not then send him with the taxi that was already attached to him before
     * and sending them the call. and removing from inActive to active
     */
    for (int i = 0; i < notActiveDriver.size(); i++) {
        Driver *d1 = notActiveDriver.front();
        if (d == d1) {
            notActiveDriver.pop_front();
            activeDrivers.push_back(d1);
            break;
        }
        notActiveDriver.pop_front();
        notActiveDriver.push_back(d1);
    }
    return;
}

/**
 * the constructor
 */
TaxiCenter::TaxiCenter() {

}

/**
 * the constructor
 */
TaxiCenter::TaxiCenter(Map mp, Socket *soc) {
    this->map = mp;
    this->socket = soc;
}

/**
 * returns the location of a given taxi
 */
Point TaxiCenter::giveLocation(int id) throw(invalid_argument) {
    for (int i = 0; i < this->notActiveDriver.size(); i++) {
        Driver *d = this->notActiveDriver.front();
        if (d->getVehicle_id() == id) {
            return d->getTaxi()->getLocation();
        }
        this->notActiveDriver.pop_front();
        this->notActiveDriver.push_back(d);
    }

    for (int i = 0; i < this->activeDrivers.size(); i++) {
        Driver *d = this->activeDrivers.front();
        if (d->getVehicle_id() == id) {
            return d->getTaxi()->getLocation();
        }
        this->activeDrivers.pop_front();
        this->activeDrivers.push_back(d);
    }
    throw invalid_argument("wrong id");
}

/**
 * delete all the node's
 */
void TaxiCenter::deleteMap() {
    this->map.freeAll();
}

void TaxiCenter::addDriverToCenter(Driver *d) {
    this->notActiveDriver.push_back(d);
}

list<Driver *> &TaxiCenter::getActiveDriver() {
    return this->activeDrivers;
}


list<Driver *> TaxiCenter::getNotActiveDriver() {
    return this->notActiveDriver;
}

void TaxiCenter::setActiveDriver(Driver *d) {
    this->activeDrivers.push_back(d);
}

void TaxiCenter::setNotActiveDriver(Driver *d) {
    this->notActiveDriver.push_back(d);
}

void TaxiCenter::addTrip(Trip t) {
    Trip trip = t;
    Point startP = t.getStartP();
    if ((startP.getX() > this->map.getSizeX()) || (startP.getY() > this->map.getSizeY())) {
        throw std::invalid_argument("invalid location");
    }
    Point endP = t.getEndP();
    if ((endP.getX() > this->map.getSizeX()) || (endP.getY() > this->map.getSizeY())) {
        throw std::invalid_argument("invalid location");
    }
    this->trips.push(t);
}

void TaxiCenter::attachTaxiToDriver(Driver *d) {
    for (int i = 0; i < this->notActiveTaxis.size(); i++) {
        Taxi *t = this->notActiveTaxis.back();
        if (t->getCarId() == d->getVehicle_id()) {
            d->setTaxi(t);
            this->notActiveTaxis.pop_back();
            return;
        }
        this->notActiveTaxis.pop_back();
        this->notActiveTaxis.push_front(t);
    }
}

list<Taxi *> TaxiCenter::getNotActiveTaxis() {
    return this->notActiveTaxis;
}

void TaxiCenter::addTaxi(Taxi *t) {
    t->setMap(this->map);
    this->notActiveTaxis.push_back(t);
}

void TaxiCenter::moveAll(Socket *s) {
    //setAllTrips();
    char *buffer = (char *) malloc(4096 * sizeof(char));
    for (int i = 0; i < this->activeDrivers.size(); i++) {
        Driver *d = this->activeDrivers.front();
        if (d->getTaxi()->getRouth().size() == 0) {
            this->activeDrivers.pop_front();
            this->activeDrivers.push_back(d);
            continue;
        }
        ssize_t n = this->socket->reciveData(buffer, 4096);
        if(strcmp(buffer,"sendMeGo") == 0){
            d->move();
            n = this->socket->sendData("9");
            this->activeDrivers.pop_front();
            this->activeDrivers.push_back(d);
        }
    }
    long size = this->activeDrivers.size();
    for (int i = 0; i < size; i++) {
        Driver *d = this->activeDrivers.front();
        d->inactivate(this->notActiveDriver, this->activeDrivers);
    }
    free(buffer);
}

bool TaxiCenter::checkTaxiAttachment(Driver *driver) {
    return (driver->getTaxi() == NULL);
}

void TaxiCenter::setAllTrips() {


}

void TaxiCenter::activateClosest(std::list<Driver *> list, Driver *driver) { //todo ??? what it is doing??
    std::list<Driver *> tempList;
    Driver *temp = list.front();
    if (list.front() == driver) {
        list.pop_front();
        this->setActiveDriver(temp);
        return;
    }
    tempList.push_back(temp);
    while (!(list.front() == driver)) {
        temp = list.front();
        list.pop_front();
        tempList.push_back(temp);
    }
    this->setActiveDriver(list.front());
    list.pop_front();
    while (tempList.size() > 0) {
        temp = tempList.front();
        tempList.pop_front();
        list.push_back(temp);
    }
}

TaxiCenter::~TaxiCenter() {
    long size = this->notActiveTaxis.size();
    for (int i = 0; i < size; i++) {
        Taxi *t = notActiveTaxis.front();
        notActiveDriver.pop_front();
        delete t;
    }
    size = this->notActiveDriver.size();
    for (int i = 0; i < size; i++) {
        Driver *d = notActiveDriver.front();
        notActiveDriver.pop_front();
        delete d;
    }
    size = this->activeDrivers.size();
    for (int i = 0; i < size; i++) {
        Driver *d = activeDrivers.front();
        activeDrivers.pop_front();
        delete d;
    }
}

void TaxiCenter::assignTrip(unsigned int time) {
    long size = this->trips.size();
    char *buffer = (char *) malloc(4096 * sizeof(char));
    for (int i = 0; i < size; i++) {
        Trip temp = this->trips.back();
        if (temp.getTime() == time) {
            ssize_t n = this->socket->reciveData(buffer, 4096);
            if (n < 0) {
                perror("Error in receive");
            }
            if (strcmp(buffer, "sendMeTrip")==0) {
                n = this->socket->sendData(""); //todo serilaze and send trip
                this->sendTrip(temp);
                if (n < 0) {
                    perror("Error in Sendto");
                }
                this->trips.pop();
            }
            break;
        } else {
            this->trips.pop();
            this->trips.push(temp);
        }
    }
    free(buffer);
}


//send taxi to driver.setTaxi in the client
//send route to driver.manage in the client