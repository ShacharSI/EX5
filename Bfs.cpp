
#include "Bfs.h"

/**
 * function that recivecs a start and an and
 * and find the shortest routh between them
 */
list<Searchable *> Bfs::findRouth(Searchable *start, Searchable *destiny, Map *m) {
    Point startPoint = start->getPoint();
    Point endPoint = destiny->getPoint();
    //todo set before bfs/
    Point currPoint = startPoint;
    std::list<Searchable *> l;
    m->setBeforeBfs();
    queue<Searchable **> q;
    Searchable *s = NULL;
    s = *m->getSearchableByCoordinate(startPoint.getX(), startPoint.getY());
    this->infoMap = new BfsInfoMap(m->getSizeX(),m->getSizeY(),m->getMap());
    this->infoMap->setVisitedSearchable(s);
    //todo check if working with queue* without sending it is a lot more faster!?!
    q = m->updateNeighbor(startPoint.getX(), startPoint.getY(), q, this->infoMap);
    while ((!q.empty()) && (!currPoint.equals(endPoint))) {
        s = *(q.front());
        q.pop(); //todo here or down there?
        currPoint = s->getPoint();
        q = m->updateNeighbor(currPoint.getX(), currPoint.getY(), q, this->infoMap);
    }

    s = *m->getSearchableByCoordinate(endPoint.getX(), endPoint.getY());
    if (s) {
        l.push_front(s);
    }
    while (s != NULL) {
        Searchable *father = this->infoMap->getFather(s);
        if (father != NULL) {
            l.push_front(father);
        }
        s = father;
    }
    return l;
}