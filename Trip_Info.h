//
// Created by haim6678 on 10/01/17.
//

#ifndef EX3_TM_TRIP_INFO_H
#define EX3_TM_TRIP_INFO_H


#include "Searchable.h"

class Trip_Info {

private:
    unsigned int tripTime;
public:
    void setTripTime(unsigned int tripTime);

private:
    list<Searchable*> routh;
public:
    unsigned int getTripTime() ;
    list<Searchable *> getRouth() ;
    Trip_Info(unsigned int time,list<Searchable*>);
};


#endif //EX3_TM_TRIP_INFO_H
