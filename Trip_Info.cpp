//
// Created by haim6678 on 10/01/17.
//

#include "Trip_Info.h"

unsigned int Trip_Info::getTripTime()  {
    return tripTime;
}

list<Searchable *>* Trip_Info::getRouth() {
    return routh;
}

Trip_Info::Trip_Info(unsigned int time, list<Searchable *>* l) {
    this->tripTime=time;
    this->routh = l;
}

void Trip_Info::setTripTime(unsigned int tripTime) {
    this->tripTime = tripTime;
}

Trip_Info::~Trip_Info() {
    delete this->routh;
}
