
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
            delete this->map[i][j];
        }
        //delete the row pointer
        delete map[i];
    }
    //delete all map
    delete this->map;

}

/**
 * c-tor of the map
 */
Map::Map(int x, int y, Searchable ***m,list<Point> obst) {
    this->sizeX = x;
    this->sizeY = y;
    this->map = m;
    this->obstacles = obst;
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
/**
 * @return the actual map of serchables
 */
Searchable ***Map::getMap() {
    return this->map;
}
/**
 * upaate one step in the bfs algo
 * @param x the x coordinate of the current searchable
 * @param y the y coordinate of the current searchable
 * @param q the current bfs algo's queue
 * @param infoMap a BfsInfoMap object
 * @return the next bfs algo's queue's state
 */
queue<Searchable **> *Map::updateNeighbor(int x, int y,
                                          std::queue<Searchable **> *q, BfsInfoMap *infoMap) {
    Searchable *curr = this->map[x][y];
    if ((((x - 1) >= 0)) && (!infoMap->isVisitedSearchable(this->map[x - 1][y]))) {
        if (!this->map[x - 1][y]->isObstacle()) {
            Searchable **temp = &this->map[x - 1][y];
            infoMap->setVisitedSearchable(*temp);
            infoMap->setSearchableFather((*temp)->getPoint(), curr->getPoint());
            Point p = infoMap->getFather((*temp)->getPoint());
            q->push(temp);
        }
    }

    if ((((y + 1) < this->sizeY)) && (!infoMap->isVisitedSearchable(this->map[x][y + 1]))) {
        if (!this->map[x][y + 1]->isObstacle()) {
            Searchable **temp = &this->map[x][y + 1];
            infoMap->setVisitedSearchable(*temp);
            infoMap->setSearchableFather((*temp)->getPoint(), curr->getPoint());
            q->push(temp);
        }
    }

    if ((((x + 1) < this->sizeX)) && (!infoMap->isVisitedSearchable(this->map[x + 1][y]))) {
        if (!this->map[x + 1][y]->isObstacle()) {
            Searchable **temp = &this->map[x + 1][y];
            infoMap->setVisitedSearchable(*temp);
            infoMap->setSearchableFather((*temp)->getPoint(), curr->getPoint());
            Point p = infoMap->getFather((*temp)->getPoint());
            q->push(temp);
        }
    }

    if ((((y - 1) >= 0)) && (!infoMap->isVisitedSearchable(this->map[x][y - 1]))) {
        if (!this->map[x][y - 1]->isObstacle()) {
            Searchable **temp = &this->map[x][y - 1];
            infoMap->setVisitedSearchable(*temp);
            infoMap->setSearchableFather((*temp)->getPoint(), curr->getPoint());
            q->push(temp);
        }
    }
    return q;
}
/**
 * set the info of each searcable to unused
 */
void Map::setBeforeBfs() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            this->map[i][j]->setBfsFather(NULL);
            this->map[i][j]->setBfsVisited(false);
        }
    }
}
/**
 * @param p point of a searchable
 * @return the searchable in this point
 */
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

int Map::validate() {
    int retVal=0;
    if((this->sizeX < 0)||(this->sizeY)) {
        retVal = -1;
    }
    while (!this->obstacles.empty()){
        Point p = this->obstacles.front();
        if((p.getX() > this->getSizeX()) ||(p.getX() < 0)
           ||(p.getY() >this->getSizeY())||(p.getY() <0)) {
            retVal = -1;
            break;
        }
        this->obstacles.pop_front();
        this->obstacles.push_back(p);
    }

    if(retVal == 0){
        int numObstacles = obstacles.size();
        for (int i = 0; i < numObstacles; i++) {
            Point p = obstacles.front();
            map[p.getX()][p.getY()]->setObstacle(true);
            obstacles.pop_front();
        }
    }
    return retVal;
}
