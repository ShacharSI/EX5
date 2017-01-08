//
// Created by sha on 1/8/17.
//

#ifndef EX3_TM_BFSVISITMAP_H
#define EX3_TM_BFSVISITMAP_H


#include <map>
#include "Searchable.h"
using namespace std;

class BfsVisitMap {
private:
    map<Searchable*,bool > visitMap;
public:
    BfsVisitMap();
    BfsVisitMap(std::list<Searchable*> searchableList);
    bool isVisitedSearchable(Searchable* searchable);
    void setvisitedSearchable(Searchable* searchable);
};


#endif //EX3_TM_BFSVISITMAP_H
