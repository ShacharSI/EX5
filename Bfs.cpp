
#include "Bfs.h"

/**
 * function that receives a start and an and
 * and find the shortest route between them
 */
list<Searchable *> Bfs::findRouth(Searchable *start, Searchable *destiny, Map *m) {
    //find the point on map
    Point startPoint = start->getPoint();
    Point endPoint = destiny->getPoint();
    Point currPoint = startPoint;
    std::list<Searchable *> l;
    //create a pair map to store values on
    BfsInfoMap bfsInfoMap(m->getSizeX(),m->getSizeY(),m->getMap());
    queue<Searchable **> q;
    Searchable *s = NULL;
    s = *m->getSearchableByCoordinate(startPoint);
    bfsInfoMap.setVisitedSearchable(s);
    //todo check if working with queue* without sending it is a lot more faster!?!
    //start the bfs process
    q = m->updateNeighbor(startPoint.getX(), startPoint.getY(), q, bfsInfoMap);
    while ((!q.empty()) && (!currPoint.equals(endPoint))) {
        s = *(q.front());
        q.pop();
        currPoint = s->getPoint();
        q = m->updateNeighbor(currPoint.getX(), currPoint.getY(), q, bfsInfoMap);
    }

    s = *m->getSearchableByCoordinate(endPoint);
    if (s) {
        l.push_front(s);
    }
    while (s != NULL) {
        Searchable *father = bfsInfoMap.getFather(s);
        if (father != NULL) {
            l.push_front(father);
        }
        s = father;
    }
    return l;
}