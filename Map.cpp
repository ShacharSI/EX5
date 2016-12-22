
#include "Map.h"

/**
 * the destructor
 */
Map::~Map() {
}

/**
 * @return - the start point of the map
 */
Searchable* Map::getStart() {
    return this->start;
}

/*
 * c-tor of the map
 */
Map::Map() {

}

/*
 * c-tor of the map
 */
void Map::freeAll() {
    while((signed)this->searchables.size() > 0) {
        Searchable* searchable = searchables.front();
        searchables.pop_front();
        delete searchable;
    }
}

/*
 * c-tor of the map
 */
Map::Map(int x, int y,Searchable * s , list<Searchable*> l) {
    this->sizeX = x;
    this->sizeY=y;
    this->start = s;
    this->searchables = l;
}

/**
 * @return - the list of obstacles on the map
 */
list<Searchable *> Map::getL(){
    return searchables;
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

Searchable *Map::findOnGrid(Point p) {
    Searchable* s = NULL;
    for (int i = 0; i <this->searchables.size() ; i++) {
        Searchable* temp = this->searchables.front();
        if(temp->getPoint().equals(p)){
            s = temp;
            this->searchables.push_back(temp);
            break;
        }
        this->searchables.pop_front();
        this->searchables.push_back(temp);
    }
    return s;
}
