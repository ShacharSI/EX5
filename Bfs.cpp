
#include "Bfs.h"
#include "Map.h"


/**
 * function that recivecs a start and an and
 * and find the shortest routh between them
 */
list<Searchable *> Bfs::findRouth(Searchable *start, Searchable *destiny, Map *m) {

    //start->setAll();
    //start->setStartVal();
    //start->createRout();

    Point startPoint = start->getPoint();
    Point endPoint = destiny->getPoint();
    Point currPoint = startPoint;
    std::list<Searchable *> l;
    m->setBeforeBfs();
    queue<Searchable **> q;
    Searchable *s = NULL;
    s = *m->getSearchableByCoordinate(startPoint.getX(),startPoint.getY());
    s->setBfsVisited(true);
    //todo check if working with queue* without sending it is a lot more faster!?!
    q = m->updateNeighbour(startPoint.getX(), startPoint.getY(), q);
    while ((!q.empty()) && (!currPoint.equals(endPoint))) {
        s = *(q.front());
        q.pop();
        currPoint = s->getPoint();
        q = m->updateNeighbour(currPoint.getX(), currPoint.getY(), q);
    }

    s = *m->getSearchableByCoordinate(endPoint.getX(),endPoint.getY());
    if(s!=NULL){
        l.push_front(s);
    }
    while (s != NULL) {
        if (s->getFather() != NULL) {
            l.push_front(s->getFather());
        }
        s = s->getFather();
    }

    return l;
}