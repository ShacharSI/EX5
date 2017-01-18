//
// Created by sha on 1/8/17.
//

#ifndef EX3_TM_BFSVISITMAP_H
#define EX3_TM_BFSVISITMAP_H


#include "Searchable.h"


using namespace std;
/**
 * class saving the bfs algo info
 * mark each searchable as visited when it's needed
 * save each searchable's father
 */
class BfsInfoMap {
private:
    bool** visitMap;
    Point** fathersMap;
    int xSize;
    int ySize;

public:
    ~BfsInfoMap();
    BfsInfoMap(int sizeX, int sizeY);
    BfsInfoMap();
    bool isVisitedSearchable(Searchable* searchable);
    Point getFather(Point current);
    void setSearchableFather(Point current,Point father);
    void setVisitedSearchable(Searchable* searchable);
    void setStarstFather(Point p );
};


#endif //EX3_TM_BFSVISITMAP_H