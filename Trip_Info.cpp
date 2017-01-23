//
// Created by haim6678 on 10/01/17.
//

#include "Trip_Info.h"

/**
 * @return the time of the trip
 */
unsigned int Trip_Info::getTripTime() {
    return tripTime;
}

/**
 * @return the route of the trip
 */
list<Searchable *> *Trip_Info::getRouth() {
    return routh;
}

/**
 * c-tor
 */
Trip_Info::Trip_Info(unsigned int time, pthread_t *pt) {
    this->tripTime = time;
    this->routh = NULL;
    this->pt = pt;
}

/**
 * default c-tor
 */
Trip_Info::~Trip_Info() {
}

int Trip_Info::validate() {
    if ((this->tripTime < 0) || (this->routh->size() == 0)) {
        return -1;   //todo empty list possible?
    }
    return 0;
}

void Trip_Info::setRoute(std::list<Searchable *> *route) {
    this->routh = route;
}

pthread_t *Trip_Info::getPthread() {
    return this->pt;
}

Point Trip_Info::getStart() {
    return this->getRouth()->front()->getPoint();
}
