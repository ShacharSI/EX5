
#include "Bfs.h"


/**
 * function that recivecs a start and an and
 * and find the shortest routh between them
 */
list<Searchable*> Bfs::findRouth(Searchable* start,Searchable* destiny) {

    start->setAll();
    start->setStartVal();
    start->createRout();

    std::list<Searchable*> l;

    l = destiny->createList();
    long j = l.size();
    for(int i = 0; i<j;i++){
        Searchable* s=l.front();
        Point p = s->getPoint();
    }
    return l;
}