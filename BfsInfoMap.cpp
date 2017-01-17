//
// Created by sha on 1/8/17.
//

#include "BfsInfoMap.h"
#include "Square.h"
#include "easyloggingpp-8.91/easylogging++.h"


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
    //getting the searchable's coordinates
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
    this->fathersMap = (Searchable ***) new Square **[sizeX];
    for (int i = 0; i < sizeX; i++) {
        this->fathersMap[i] = new Searchable *[sizeY];
        this->visitMap[i] = new bool[sizeY];
        for (int j = 0; j < sizeY; j++) {
            this->visitMap[i][j] = false;
            this->fathersMap[i][j] = NULL;
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
Searchable *BfsInfoMap::getFather(Searchable *current) {
    Point searchableLocation = current->getPoint();
    int xCoordinate = searchableLocation.getX();
    int yCoordinate = searchableLocation.getY();
    return this->fathersMap[xCoordinate][yCoordinate];
}
/**
 * set the Searchable's Father
 * @param son a serchable
 * @param current the son's father in the bfs's route
 */
void BfsInfoMap::setSearchableFather(Searchable *son, Searchable *current) {
    Point searchableLocation = son->getPoint();
    int xCoordinate = searchableLocation.getX();
    int yCoordinate = searchableLocation.getY();
    this->fathersMap[xCoordinate][yCoordinate] = current;
}
/**
 * d-tor
 */
BfsInfoMap::~BfsInfoMap() {

    for (int i = 0; i < xSize; ++i) {
        for (int j = 0; j < ySize; ++j) {
            //delete colomn searchables
            delete (this->fathersMap[i][j]);
        }
        //delete the row pointer
        delete (fathersMap[i]);
    }
    delete this->fathersMap;

    for (int i = 0; i < xSize; ++i) {
        delete this->visitMap[i];
    }
    delete this->visitMap;
}
