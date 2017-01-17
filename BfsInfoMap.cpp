//
// Created by sha on 1/8/17.
//

#include "BfsInfoMap.h"
#include "Square.h"
#include "easyloggingpp-8.91/easylogging++.h"


BfsInfoMap::BfsInfoMap() {

}

bool BfsInfoMap::isVisitedSearchable(Searchable *searchable) {
    Point searchableLocation = searchable->getPoint();
    int xCoordinate = searchableLocation.getX();
    int yCoordinate = searchableLocation.getY();
    return this->visitMap[xCoordinate][yCoordinate];
}

BfsInfoMap::BfsInfoMap(int sizeX, int sizeY) {
    this->xSize = sizeX;
    this->ySize = sizeY;
    this->visitMap = new bool *[sizeX];
    this->fathersMap = (Searchable***)new Square **[sizeX];
    for (int i = 0; i < sizeX; i++) {
        this->fathersMap[i] = new Searchable *[sizeY];
        this->visitMap[i] = new bool [sizeY];
        for (int j = 0; j < sizeY; j++) {
            this->visitMap[i][j] = false;
            this->fathersMap[i][j] = NULL;
        }
    }
}
    void BfsInfoMap::setVisitedSearchable(Searchable *searchable) {
        Point searchableLocation = searchable->getPoint();
        int xCoordinate = searchableLocation.getX();
        int yCoordinate = searchableLocation.getY();
        this->visitMap[xCoordinate][yCoordinate] = true;
    }

    Searchable *BfsInfoMap::getFather(Searchable *current) {
        Point searchableLocation = current->getPoint();
        int xCoordinate = searchableLocation.getX();
        int yCoordinate = searchableLocation.getY();
        return this->fathersMap[xCoordinate][yCoordinate];
    }

    void BfsInfoMap::setSearchableFather(Searchable *son, Searchable *current) {
        Point searchableLocation = son->getPoint();
        int xCoordinate = searchableLocation.getX();
        int yCoordinate = searchableLocation.getY();
        this->fathersMap[xCoordinate][yCoordinate] = current;
    }

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
