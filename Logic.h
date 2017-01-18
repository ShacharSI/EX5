

#ifndef TM_LOGIC_H
#define TM_LOGIC_H

#include "Square.h"
#include "Bfs.h"
#include "Map.h"
#include "MapFactory.h"
/**
 * a class that is in charge of the game logic
 * takes the map size as a parameter and old a map
 * and the bfs class.
 */
class Logic{

public:
    Logic();
    Logic(vector<int> sizes);
    int getSizeX();
    int getSizeY();
    Map* createNewMap(string s);
    void validate();
    void setObstacle(int numObstacle);
    list <Point> getObstacle();
private:
    int sizeX;
    int sizeY;
    MapFactory mpFactory;
    list<Point> obstacle;
};


#endif //TM_LOGIC_H