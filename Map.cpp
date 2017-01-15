
#include <queue>
#include "Map.h"
#include <stdexcept>

#define MAX_SIZE 2000

/**
 * the destructor
 */
Map::~Map() {
    this->freeAll();
}


//
/**
 * c-tor of the map
 */
Map::Map() {

}

/**
 * c-tor of the map
 */
void Map::freeAll() {
    for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            //delete colomn searchables
            delete (this->map[i][j]);
        }
        //delete the row pointer
        delete (map[i]);
    }
    //delete all map
    delete (this->map);

}

/**
 * c-tor of the map
 */
Map::Map(int x, int y, Searchable ***m) {
    this->sizeX = x;
    this->sizeY = y;
    this->map = m;
    //create the map
}

/**
 * @return - the map's x size
 */
int Map::getSizeX() const {
    return sizeX;
}

/**
 * @return - the map's x size
 */
int Map::getSizeY() const {
    return sizeY;
}

Searchable ***Map::getMap() {
    return this->map;
}

queue<Searchable **>* Map::updateNeighbor(int x, int y,
                                         std::queue<Searchable **>* q, BfsInfoMap* infoMap) {
    Searchable *curr = this->map[x][y];
    //curr->setBfsVisited(true);
    //curr->setBfsFather(NULL);
    //TODO add obstacle chaeck!!
    if ((((x - 1) >= 0)) && (!infoMap->isVisitedSearchable(this->map[x - 1][y]))) {
        Searchable **temp = &this->map[x - 1][y];
        infoMap->setVisitedSearchable(*temp);
        infoMap->setSearchableFather(*temp, curr);
        q->push(temp);
    }

    if ((((x + 1) < this->sizeX)) && (!infoMap->isVisitedSearchable(this->map[x + 1][y]))) {
        Searchable **temp = &this->map[x + 1][y];
        infoMap->setVisitedSearchable(*temp);
        infoMap->setSearchableFather(*temp, curr);
        q->push(temp);
    }

    if ((((y + 1) < this->sizeY)) && (!infoMap->isVisitedSearchable(this->map[x][y + 1]))) {
        Searchable **temp = &this->map[x][y + 1];
        infoMap->setVisitedSearchable(*temp);
        infoMap->setSearchableFather(*temp, curr);
        q->push(temp);
    }

    if ((((y - 1) >= 0)) && (!infoMap->isVisitedSearchable(this->map[x][y - 1]))) {
        Searchable **temp = &this->map[x][y - 1];
        infoMap->setVisitedSearchable(*temp);
        infoMap->setSearchableFather(*temp, curr);
        q->push(temp);
    }
    return q;
}

void Map::setBeforeBfs() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            this->map[i][j]->setBfsFather(NULL);
            this->map[i][j]->setBfsVisited(false);
        }
    }
}

Searchable **Map::getSearchableByCoordinate(Point p) {
    if ((p.getY() < 0) || (p.getX() < 0)
        || (p.getX() > this->getSizeX())
        || (p.getY() > this->getSizeY())) {
        throw invalid_argument("wrong coordinate for point");

    }
    int x = p.getX();
    int y = p.getY();
    return &this->map[x][y];
}
