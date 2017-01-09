#ifndef EX1TM_BFS_H
#define EX1TM_BFS_H
#include <list>
#include "Square.h"
#include "Algorithm.h"
#include "Map.h"

/**
 * a class that is in charge of finding the
 * shortest route between 2 pointsx
 */
class Bfs: public Algorithm {
private:
    BfsInfoMap* infoMap;

public:
    list<Searchable*> findRouth(Searchable* start,Searchable* destiny,Map* m);
};


#endif //EX1TM_BFS_H