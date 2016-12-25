
#ifndef EX1TM_BFS_H
#define EX1TM_BFS_H
#include <list>
#include "Square.h"
#include "Algorithm.h"

/**
 * a class that is in charge of finding the
 * shrtest rou between 2 points
 */
class Bfs: public Algorithm {


public:
    list<Searchable*> findRouth(Searchable* start,Searchable* destiny);
private:


};


#endif //EX1TM_BFS_H