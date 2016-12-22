

#ifndef EX1TM_MANEGEMANT_H
#define EX1TM_MANEGEMANT_H

#include <list>
#include "Point.h"
#include "Searchable.h"
#include "list"


/**
 * class that in charge of olding the relevant information and managing a map.
 */
class Map {

public:
    ~Map();
    Map();
    Map(int sizeX, int sizeY, Searchable* start, list<Searchable*> l);
    void freeAll();
    Searchable* getStart();
    bool operator==(const Map &other) const {
        return this->searchables == other.searchables;
    }
    list<Searchable *> getL();
    int getSizeX() const;
    int getSizeY() const;
    Searchable* findOnGrid(Point p);


private:
    int sizeX;
    int sizeY;
    Searchable* start;
    list<Searchable*> obstacle;
    std::list<Searchable*> searchables;
};


#endif //EX1TM_MANEGEMANT_H