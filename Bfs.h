#ifndef EX1TM_BFS_H
#define EX1TM_BFS_H
#include "Square.h"
#include "Algorithm.h"
#include "Map.h"
#include "BfsInfoMap.h"
//
/**
 * a class that is in charge of finding the
 * shortest route between 2 points
 */
class Bfs: public Algorithm {
private:
    //BfsInfoMap* infoMap;

public:
    list<Searchable*>* findRouth(Searchable* start,Searchable* destiny,Map* m);
    static void* findRouthRunner(void*);
};

typedef struct{
    Searchable * start;
    Searchable * end;
    Map* map;
    Bfs*  bfsPointer;
    std::list<Searchable *>* list;
}bfsThreadStruct;

#endif //EX1TM_BFS_H