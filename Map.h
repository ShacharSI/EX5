
#ifndef EX1TM_MANEGEMANT_H
#define EX1TM_MANEGEMANT_H

#include <list>
#include "Point.h"
#include "Searchable.h"
#include "BfsInfoMap.h"
#include <queue>

//
/**
 * class that in charge of holding the relevant information and managing a map.x
 */
class Map {

public:
    ~Map();


    Map(int sizeX, int sizeY, Searchable ***map);

    void freeAll();

    /* bool operator==(const Map &other) const {
         return this->searchables == other.searchables;
     }*/
    Searchable **getSearchableByCoordinate(Point p);

    int getSizeX() const;

    int getSizeY() const;

    Searchable ***getMap();

    queue<Searchable **>* updateNeighbor(int x, int y, std::queue<Searchable **>* q,
                                         BfsInfoMap* visitMap);

private:
    int sizeX;
    int sizeY;
    Searchable ***map;
    list<Searchable*> l;
};


#endif //EX1TM_MANEGEMANT_H