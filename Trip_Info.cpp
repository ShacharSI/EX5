//
// Created by haim6678 on 10/01/17.
//

#include "Trip_Info.h"
/**
 * @return the time of the trip
 */
unsigned int Trip_Info::getTripTime()  {
    return tripTime;
}
/**
 * @return the route of the trip
 */
list<Searchable *>* Trip_Info::getRouth() {
    return routh;
}
/**
 * c-tor
 */
Trip_Info::Trip_Info(unsigned int time, list<Searchable *>* l) {
    this->tripTime=time;
    this->routh = l;
}

/**
 * default c-tor
 */
Trip_Info::~Trip_Info() {
}
