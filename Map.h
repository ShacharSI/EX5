

#ifndef EX1TM_MANEGEMANT_H
#define EX1TM_MANEGEMANT_H

#include <list>
#include "Point.h"
#include "Searchable.h"
#include "list"
#include <queue>


/**
 * class that in charge of olding the relevant information and managing a map.
 */
class Map {

public:
    ~Map();

    Map();

    Map(int sizeX, int sizeY, Searchable ***map);

    void freeAll();

    /* bool operator==(const Map &other) const {
         return this->searchables == other.searchables;
     }*/
    Searchable **getSearchableByCoordinate(int x, int y);

    void setBeforeBfs();

    list<Searchable *> getL();

    int getSizeX() const;

    int getSizeY() const;

    Searchable ***getMap();

    queue<Searchable **> updateNeighbour(int x, int y, std::queue<Searchable **> q);

    Searchable *getFather(Searchable *);

    bool checkVal(int x, int y);

private:
    int sizeX;
    int sizeY;
    Searchable ***map;

    list<Searchable*> l; //todo set this list
};


#endif //EX1TM_MANEGEMANT_H