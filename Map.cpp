
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
/**
 *
 * @param x the x coordinate of the current searchable
 * @param y the y coordinate of the current searchable
 * @param q the current bfs algo's queue
 * @param infoMap a BfsInfoMap object
 * @return the next bfs algo's queue's state
 */
queue<Searchable **> *Map::updateNeighbor(int x, int y,
                                          std::queue<Searchable **> *q, BfsInfoMap *infoMap) {
    //gets the current searchable by its coordinates
    Searchable *curr = this->map[x][y];
    //checks whether to insert the current's left neighbor
    if ((((x - 1) >= 0)) && (!infoMap->isVisitedSearchable(this->map[x - 1][y]))) {
        if (!this->map[x - 1][y]->isObstacle()) {
            Searchable **temp = &this->map[x - 1][y];
            infoMap->setVisitedSearchable(*temp);
            infoMap->setSearchableFather(*temp, curr);
            q->push(temp);
        }
    }
    //checks whether to insert the current's right neighbor
    if ((((x + 1) < this->sizeX)) && (!infoMap->isVisitedSearchable(this->map[x + 1][y]))) {
        if (!this->map[x + 1][y]->isObstacle()) {
            Searchable **temp = &this->map[x + 1][y];
            infoMap->setVisitedSearchable(*temp);
            infoMap->setSearchableFather(*temp, curr);
            q->push(temp);
        }
    }
    //checks whether to insert the current's upper neighbor
    if ((((y + 1) < this->sizeY)) && (!infoMap->isVisitedSearchable(this->map[x][y + 1]))) {
        if (!this->map[x][y + 1]->isObstacle()) {
            Searchable **temp = &this->map[x][y + 1];
            infoMap->setVisitedSearchable(*temp);
            infoMap->setSearchableFather(*temp, curr);
            q->push(temp);
        }
    }
    //checks whether to insert the current's lower neighbor
    if ((((y - 1) >= 0)) && (!infoMap->isVisitedSearchable(this->map[x][y - 1]))) {
        if (!this->map[x][y - 1]->isObstacle()) {
            Searchable **temp = &this->map[x][y - 1];
            infoMap->setVisitedSearchable(*temp);
            infoMap->setSearchableFather(*temp, curr);
            q->push(temp);
        }
    }
    return q;
}
/**
 * @param p point of a searchable
 * @return the searchable in this point
 */
Searchable **Map::getSearchableByCoordinate(Point p) {
    //check p's validity
    if ((p.getY() < 0) || (p.getX() < 0)
        || (p.getX() > this->getSizeX())
        || (p.getY() > this->getSizeY())) {
        throw invalid_argument("wrong coordinate for point");

    }
    //find and return the searchable
    int x = p.getX();
    int y = p.getY();
    return &this->map[x][y];
}
