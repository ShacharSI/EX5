

#include "MapFactory.h"

/**
 *return a map of an implement of Searchable according to a string.
 */
Map *MapFactory::createMapSearchable(string s, int sizeX, int sizeY,
                                int currentX, int currentY, list <Point> obatacle) {
    //if the string is "Square" return a map of squares
    if (s.compare("Square") == 0) {
        Searchable ***grid = createMapSquare(sizeX, sizeY, obatacle);
        return new Map(sizeX, sizeY, grid);
    }
}

/**
 * checking if a given point is in the obstacle list
 */
bool MapFactory::checkObstacle(int currentX, int currentY, list <Point> obatacle) {
    Point p(currentX, currentY);
    for (int i = 0; i < obatacle.size(); i++) {
        Point tempCheck = obatacle.front();
        if (p.equals(tempCheck)) {
            return true;
        }
        obatacle.pop_front();
        obatacle.push_back(tempCheck);
    }
    return false;
}


/**
 * create a map of squares
 */
Searchable ***MapFactory::createMapSquare(int sizeX, int sizeY, list <Point> obatacle) {


    Searchable ***map = (Searchable***)new Square **[sizeX];
    //Searchable*** map = new Searchable** [sizeY];

    //create the map
    for (int i = 0; i < sizeX; i++) {
        //create a row
        map[i] = new Searchable *[sizeY];
        //create a column
        for (int j = 0; j < sizeY; j++) {
            Searchable *s = (Searchable*)new Square(i,j);
            //initialize vals
            s->setBfsFather(NULL);
            s->setBfsVisited(false);
            s->setObstacle(false);
            //enter the node to the map
            map[i][j] = s;
        }
    }

    int numObstacles = obatacle.size();
    for (int i = 0; i < numObstacles; i++) {
        Point p = obatacle.front();
        map[p.getX()][p.getY()]->setObstacle(true);
        obatacle.pop_front();
    }
    return map; //todo will work the casting?
}

/**
* check whether the new square is already exist and return it.
* if it doesn't exist, return null
*/
Square *MapFactory::getSquare(int x, int y, list<Searchable *> l) {
    Point p(x, y);
    for (int i = 0; i < l.size(); i++) {
        Searchable *s = l.front();
        l.pop_front();
        if (s->getPoint().equals(p)) {
            l.push_back(s);
            return (Square *) s;
        }
        l.push_back(s);
    }

    return NULL;
}