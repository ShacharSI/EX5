
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


    Map(int sizeX, int sizeY, Searchable ***map,list<Point> obst);

    void freeAll();

    /* bool operator==(const Map &other) const {
         return this->searchables == other.searchables;
     }*/
    Searchable **getSearchableByCoordinate(Point p);

    void setBeforeBfs();

    int getSizeX() const;

    int getSizeY() const;

    Searchable ***getMap();

    queue<Searchable **>* updateNeighbor(int x, int y, std::queue<Searchable **>* q,
                                         BfsInfoMap* visitMap);

    bool checkVal(int x, int y);

    int validate();
private:
    int sizeX;
    int sizeY;
    Searchable ***map;
    list<Point> obstacles;
};


#endif //EX1TM_MANEGEMANT_H