//
// Created by sha on 12/15/16.
//

#ifndef TM_ALGORITHM_H
#define TM_ALGORITHM_H


#include "Searchable.h"
#include "Map.h"

/**
 * an interface of serching a routh between point on map
 */
class Algorithm{
public:
    virtual list<Searchable*>* findRouth(Searchable* start,Searchable* destiny,Map* m) = 0;
};
#endif //TM_ALGORITHM_H