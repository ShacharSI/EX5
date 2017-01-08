
#include <queue>
#include "Map.h"

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
        //delete the row pointe
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

queue<Searchable **> Map::updateNeighbour(int x, int y, std::queue<Searchable **> q) {

    Searchable *curr = this->map[x][y];
    //curr->setBfsVisited(true);
    //curr->setBfsFather(NULL);
    //todo add obsatcle check!!
    if ((((x - 1) >= 0)) && (!this->map[x - 1][y]->getBfsVisited())) {
        this->map[x - 1][y]->setBfsFather(curr);
        this->map[x - 1][y]->setBfsVisited(true);
        q.push(&this->map[x - 1][y]);
    }

    if ((((x + 1) < this->sizeX)) && (!this->map[x + 1][y]->getBfsVisited())) {
        this->map[x + 1][y]->setBfsFather(curr);
        this->map[x + 1][y]->setBfsVisited(true);
        q.push(&this->map[x + 1][y]);
    }

    if ((((y + 1) < this->sizeY)) && (!this->map[x][y + 1]->getBfsVisited())) {
        this->map[x][y + 1]->setBfsFather(curr);
        this->map[x][y + 1]->setBfsVisited(true);
        q.push(&this->map[x][y + 1]);
    }

    if ((((y - 1) >= 0)) && (!this->map[x][y - 1]->getBfsVisited())) {
        this->map[x][y - 1]->setBfsFather(curr);
        this->map[x][y - 1]->setBfsVisited(true);
        q.push(&this->map[x][y - 1]);
    }


    return q;
}

Searchable *Map::getFather(Searchable *s) {
    return s->getFather();
}

void Map::setBeforeBfs() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            this->map[i][j]->setBfsFather(NULL);
            this->map[i][j]->setBfsVisited(false);
        }
    }
}

Searchable **Map::getSearchableByCoordinate(int x, int y) {
    //todo validate coordinnate
    return &this->map[x][y];
}



