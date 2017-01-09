//
// Created by sha on 1/8/17.
//

#include "BfsInfoMap.h"

BfsInfoMap::BfsInfoMap() {

}

/*
 * check whether the searchable is visited
 */
bool BfsInfoMap::isVisitedSearchable(Searchable *searchable) {
    return this->visitMap[searchable];
}

BfsInfoMap::BfsInfoMap(int sizeX, int sizeY, Searchable *** map) {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            this->visitMap[map[i][j]] = false;
            this->fathersMap[map[i][j]] = NULL;
        }
    }
}
    void BfsInfoMap::setVisitedSearchable(Searchable *searchable) {
        this->visitMap[searchable] = true;
    }

    Searchable *BfsInfoMap::getFather(Searchable *current) {
        return this->fathersMap[current];
    }

    void BfsInfoMap::setSearchableFather(Searchable *son, Searchable *current) {
        this->fathersMap[son] = current;
    }
