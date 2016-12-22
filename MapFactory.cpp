

#include "MapFactory.h"
/**
 *return a map of an implement of Searchable according to a string.
 */
Map MapFactory::createMapSearchable(string s, int sizeX, int sizeY,int currentX,int currentY,list<Point> obatacle) {
    //if the string is "Square" retun a map of squares
    if (s.compare("Square") == 0){
        Searchable* start = createMapSquare(sizeX,sizeY, currentX, currentY,obatacle);
        return Map(sizeX,sizeY,start,this->s);
    }
}

/**
 * checking if a given point is in the obstacle list
 */
bool MapFactory::checkObstacle(int currentX, int currentY, list <Point> obatacle) {
    Point p(currentX,currentY);
    for(int i =0;i< obatacle.size();i++){
        Point tempCheck = obatacle.front();
        if(p.equals(tempCheck)){
            return true;
        }
        obatacle.pop_front();
        obatacle.push_back(tempCheck);
    }
    return false;
}


/*
 * create a map of squares
 */
Square* MapFactory::createMapSquare(int sizeX, int sizeY,int currentX,int currentY,list<Point> obatacle) {
    //if the point is out of limits return NULL
    if((currentX > sizeX -1)|| (currentY > sizeY -1)||(currentX < 0)||(currentY < 0)||(checkObstacle(currentX,currentY,obatacle))){
        return NULL;
    }
    //create a square and insert it to the list of the squares
    Point temp = Point(currentX,currentY);
    Square* start = new Square(temp);
    Searchable* searchable = start;
    s.push_back( searchable);
    //set the upper neighbor of the square
    if((start->upperSon == NULL)&&(start->getSon() < 4)){
        start->setSon(1);
        //if the square is already exist set the exist neighbor
        if(this->getSquare(currentX,currentY +1,s) != NULL){
            start->upperSon = this->getSquare(currentX,currentY +1,s);
        } else{
            //create the neighbor and set it as visited
            start->setVisitU(true);
            start->SetUpper(this->createMapSquare(sizeX, sizeY, currentX ,currentY +1,obatacle));
        }
    }
    //set the botoom neighbor of the square
    if((start->bottomSon == NULL)&&(start->getSon() < 4)){
        start->setSon(1);
        //if the square is already exist set the exist neighbor
        if(this->getSquare(currentX,currentY -1,s) != NULL){
            start->bottomSon=this->getSquare(currentX,currentY -1,s);
        } else{
            //create the neighbor and set it as visited
            start->setVisitB(true);
            start->SetBottom(this->createMapSquare(sizeX, sizeY,currentX ,currentY -1,obatacle));
        }
    }
    //set the right neighbor of the square
    if((start->rightSon == NULL)&&(start->getSon() < 4)){
        Point p = Point(0,0);
        if(p.equals(start->getPoint())){
        }
        //if the square is already exist set the exist neighbor
        start->setSon(1);
        if(this->getSquare(currentX +1,currentY,s) != NULL){
            start->rightSon = this->getSquare(currentX+1,currentY,s);
        }else{
            //create the neighbor and set it as visited
            start->setVisitR(true);
            start->SetRight(this->createMapSquare(sizeX, sizeY,currentX +1,currentY,obatacle));
        }
    }
    //set the left neighbor of the square
    if((start->leftSon == NULL)&&(start->getSon() < 4)) {
        start->setSon(1);
        //if the square is already exist set the exist neighbor
        if(this->getSquare(currentX-1,currentY,s) != NULL){
            start->leftSon = this->getSquare(currentX -1,currentY,s);
        }else{
            //create the neighbor and set it as visited
            start->setVisitL(true);
            start->SetLeft(this->createMapSquare(sizeX, sizeY,currentX - 1, currentY,obatacle));
        }
    }
    return start;
}

/*
* check whether the new square is already exist and return it.
* if it doesn't exist, return null
*/
Square* MapFactory ::getSquare(int x, int y, list<Searchable *> l) {
    Point p(x,y);
    for(int i=0;i<l.size();i++){
        Searchable* s =l.front();
        l.pop_front();
        if(s->getPoint().equals(p)){
            l.push_back(s);
            return (Square*) s;
        }
        l.push_back(s);
    }

    return NULL;
}