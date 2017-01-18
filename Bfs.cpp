
#include "Bfs.h"


/**
 * function that receives a start and an and
 * and find the shortest route between them
 */
list<Searchable *> *Bfs::findRouth(Searchable *start, Searchable *destiny, Map *m) {
    //find the point on map
    Point startPoint = start->getPoint();
    Point endPoint = destiny->getPoint();
    Point currPoint = startPoint;
    std::list<Searchable *> *l = new list<Searchable *>;
    //create a pair map to store values on
    BfsInfoMap *bfsInfoMap = new BfsInfoMap(m->getSizeX(), m->getSizeY());
    queue<Searchable **> *q = new queue<Searchable **>;
    Searchable *s = NULL;
    s = *m->getSearchableByCoordinate(startPoint);
    bfsInfoMap->setVisitedSearchable(s);
    bfsInfoMap->setStarstFather(s->getPoint());
    //start the bfs process
    q = m->updateNeighbor(startPoint.getX(), startPoint.getY(), q, bfsInfoMap);
    while ((!q->empty()) && (!currPoint.equals(endPoint))) {
        s = *(q->front());
        q->pop();
        currPoint = s->getPoint();
        q = m->updateNeighbor(currPoint.getX(), currPoint.getY(), q, bfsInfoMap);
    }
    Searchable* star =*m->getSearchableByCoordinate(startPoint);
    s = *m->getSearchableByCoordinate(endPoint);
    if (s) {
        l->push_front(s);
    }

    while (!bfsInfoMap->getFather(s->getPoint()).equals(bfsInfoMap->getFather(star->getPoint()))) {

        Point fatherPoint = bfsInfoMap->getFather(s->getPoint());
        Searchable *father = *m->getSearchableByCoordinate(fatherPoint);

        l->push_front(father);

        s = father;

    }

    if((!bfsInfoMap->getFather(s->getPoint()).equals(Point(-1,-1)))){
        Point fatherPoint = bfsInfoMap->getFather(s->getPoint());
        Searchable *father = *m->getSearchableByCoordinate(fatherPoint);
        l->push_front(father);
    }


    delete bfsInfoMap;
    delete q;
    return l;
}