//
// Created by sha on 1/8/17.
//

#include "BfsVisitMap.h"

BfsVisitMap::BfsVisitMap() {

}

bool BfsVisitMap::isVisitedSearchable(Searchable *searchable) {
    return this->visitMap[searchable];
}

BfsVisitMap::BfsVisitMap(std::list<Searchable *> searchableList) {
    long size = searchableList.size();
    for(int i= 0;i<size;i++) {
        Searchable* current = searchableList.front();
        searchableList.pop_front();
        this->visitMap[current] = false;
    }
}

void BfsVisitMap::setvisitedSearchable(Searchable *searchable) {
    this->visitMap[searchable] = true;
}
