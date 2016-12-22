

#ifndef TM_MAPFACTORY_H
#define TM_MAPFACTORY_H

#include "Searchable.h"
#include "Square.h"
#include "Map.h"

/**
 * class of factory. Create a map of Searchables.
 */
class MapFactory{
private:
    list<Searchable*> s;
    Square* createMapSquare(int sizeX, int SizeY,int currentX,int currentY,list<Point> obatacle);
    Square* getSquare(int x, int y, list<Searchable *> l);
    bool checkObstacle(int currentX,int currentY,list<Point> obatacle);
public:
    Map createMapSearchable(string S,int sizeX, int SizeY,int currentX,int currentY,list<Point> obatacle);
    MapFactory() {

    }
};

#endif //TM_MAPFACTORY_H