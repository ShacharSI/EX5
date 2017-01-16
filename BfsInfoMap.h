//
// Created by sha on 1/8/17.
//

#ifndef EX3_TM_BFSVISITMAP_H
#define EX3_TM_BFSVISITMAP_H

#include <map>
#include <queue>
#include "Searchable.h"

using namespace std;

class BfsInfoMap {
private:
    bool** visitMap;
    Searchable*** fathersMap;
    int xSize;
    int ySize;
public:
    ~BfsInfoMap();
    BfsInfoMap(int sizeX, int sizeY);
    BfsInfoMap();
    bool isVisitedSearchable(Searchable* searchable);
    Searchable* getFather(Searchable *current);
    void setSearchableFather(Searchable* current,Searchable* father);
    void setVisitedSearchable(Searchable* searchable);
};


#endif //EX3_TM_BFSVISITMAP_H
