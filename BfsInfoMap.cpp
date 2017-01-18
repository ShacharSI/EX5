//
// Created by sha on 1/8/17.
//

#include "BfsInfoMap.h"

/**
 * default c-tor
 */
BfsInfoMap::BfsInfoMap() {

}
/**
 * @param searchable
 * @return whether this searchable is visited
 */
bool BfsInfoMap::isVisitedSearchable(Searchable *searchable) {
    Point searchableLocation = searchable->getPoint();
    int xCoordinate = searchableLocation.getX();
    int yCoordinate = searchableLocation.getY();
    return this->visitMap[xCoordinate][yCoordinate];
}
/**
 * c-tor
 * setting empty visitMap and empty fatherMap
 * @param sizeX the width of the map
 * @param sizeY the length of the map
 */
BfsInfoMap::BfsInfoMap(int sizeX, int sizeY) {
    this->xSize = sizeX;
    this->ySize = sizeY;
    this->visitMap = new bool *[sizeX];
    this->fathersMap = new Point *[sizeX];
    for (int i = 0; i < sizeX; i++) {
        this->visitMap[i] = new bool[sizeY];
        this->fathersMap[i] = new Point[sizeY];
        for (int j = 0; j < sizeY; j++) {
            this->visitMap[i][j] = false;
            this->fathersMap[i][j] = Point(-1,-1);
        }
    }
}
/**
 * set a searchable as visited
 * @param searchable
 */
void BfsInfoMap::setVisitedSearchable(Searchable *searchable) {
    Point searchableLocation = searchable->getPoint();
    int xCoordinate = searchableLocation.getX();
    int yCoordinate = searchableLocation.getY();
    this->visitMap[xCoordinate][yCoordinate] = true;
}
/**
 * @param current a searchable in the map
 * @return this searchable's father
 */
Point BfsInfoMap::getFather(Point current) {
    return fathersMap[current.getX()][current.getY()];

}
/**
 * set the Searchable's Father
 * @param son a serchable
 * @param current the son's father in the bfs's route
 */
void BfsInfoMap::setSearchableFather(Point son, Point current) {
    this->fathersMap[son.getX()][son.getY()] = current;
}
/**
 * d-tor
 */
BfsInfoMap::~BfsInfoMap() {
    for (int i = 0; i < xSize; i++) {
        delete [](this->fathersMap[i]);
    }
    delete this->fathersMap;

    for (int i = 0; i < xSize; i++) {
        delete this->visitMap[i];
    }
    delete this->visitMap;
}

void BfsInfoMap::setStarstFather(Point p) {
    this->fathersMap[p.getX()][p.getY()] = p;
}