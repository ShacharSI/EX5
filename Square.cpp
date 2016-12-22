

#include <limits>
#include <queue>
#include "Point.h"
#include "Square.h"
#include "Bfs.h"

/**
 * @return - the square point.
 */
Point Square::getPoint() {
    return this->point;
}

/**
 * @param s - the parm to set the left node
 */
void Square::SetLeft(Square *s) {
    this->leftSon = s;
}

/**
 * @param s - the parm to set the upper node
 */
void Square::SetUpper(Square *s) {
    this->upperSon = s;
}

/**
 * @param s - the current bfs val
 */
int Square::getBfsVal() {
    return this->bfsVal;
}

/**
 * checking if a current bfs val is bigger then the routh to it +1
 * @param start - the rout from start to it
 * @param des - the destiny
 * @return - true if bigger
 */
bool Square::checkVal(Square* start,Square* des){
    return ((start->getBfsVal() + 1)<(des->getBfsVal()));
}

/**
 * @return - the list that represnt the routh
 * between start and dest.
 */
list<Searchable*> Square::createList() {

    std::list<Searchable*> s;
    Square* father = this;

    while (father!= NULL){
        Searchable* temp = father;
        s.push_front(temp);
        father = father->getBstFather();
    }
    return s;
}

/**
 * seting the start bfs argumants
 */
void Square::setStartVal() {
    this->bfsVal=0;
    this->bfsFather = NULL;
}


/**
 * updating node neiboghrs bfs val.acoording to the algorithm
 */
queue<Square*> Square::updateNeiboghr(queue<Square*> q) {

    //updating all the ond's neighbors
    if((this->getLeft()!= NULL)&&(this->checkVal(this,this->getLeft()))&&(!this->getLeft()->bfsVisited)){
        this->getLeft()->setBfsVal(this->getBfsVal() +1);
        this->getLeft()->setBfsFather(this);
        q.push(this->getLeft());
        this->getLeft()->bfsVisited= true;
    }
    if((this->getUpper()!= NULL)&&(this->checkVal(this,this->getUpper()))&&(!this->getUpper()->bfsVisited)){
        this->getUpper()->setBfsVal(this->getBfsVal() +1);
        this->getUpper()->setBfsFather(this);
        q.push(this->getUpper());
        this->getUpper()->bfsVisited= true;
    }
    if((this->getRight()!= NULL)&&(this->checkVal(this,this->getRight()))&&(!this->getRight()->bfsVisited)){
        this->getRight()->setBfsVal(this->getBfsVal() +1);
        this->getRight()->setBfsFather(this);
        q.push(this->getRight());
        this->getRight()->bfsVisited= true;
    }
    if((this->getBotoom()!= NULL)&&(this->checkVal(this,this->getBotoom()))&&(!this->getBotoom()->bfsVisited)){
        this->getBotoom()->setBfsVal(this->getBfsVal() +1);
        this->getBotoom()->setBfsFather(this);
        q.push(this->getBotoom());
        this->getBotoom()->bfsVisited= true;
    }
    return q;
}

/**
 * creating the shortest routh between start and all
 * the other point.
 */
void Square::createRout(){
    queue<Square*> q;
    q = this->updateNeiboghr(q);
    while (!q.empty()) {
        Square* s = q.front();
        q = s->updateNeiboghr(q);
        q.pop();
    }
}

/**
 * setting the initial bfs val for all nodes
 */
void Square::setAll() {

    //setting all the node to default values
    this->setVisited(true);
    if(((this->bottomSon!= NULL))&&(!this->getBotoom()->getVisited())) {
        this->visitBottom = false;
        this->getBotoom()->setAll();
    }
    if((this->leftSon!= NULL)&&(!this->getLeft()->getVisited())){
        this->visitLeft = false;
        this->getLeft()->setAll();
    }
    if((this->rightSon!= NULL)&&(!this->getRight()->getVisited())){
        this->visitRIght = false;
        this->getRight()->setAll();
    }
    if((this->upperSon!= NULL)&&(!this->getUpper()->getVisited())){
        this->visitUp= false;
        this->getUpper()->setAll();
    }

    this->setBfsVal(std::numeric_limits<int>::max());
    this->setBfsFather(NULL);
    this->visitToFind= false;
    this->bfsVisited= false;
    this->visitRIght = false;
}



/**
 * @param s - the parm to set the right node
 */
void Square::SetRight(Square *s) {
    this->rightSon = s;
}

/**
 * @param s - the parm to set the num of sons for the square
 */
void Square::setSon(int num) {
    this->numSon = numSon + num;
}

/**
 * @return - the num of sons for a square
 */
int Square::getSon() {
    return this->numSon;
}

/**
 * the constructor.
 * @param x - the square x coordinade
 * @param y -  the square y coordinade
 */
Square::Square(int x, int y) {
    Point p(x, y);
    this->point = p;
    this->numSon = 0;
    this->bfsVal =0;
    this->leftSon=NULL;
    this->SetBottom(NULL);
    this->rightSon=NULL;
    this->upperSon=NULL;
    this->visitBottom = false;
    this->visitUp = false;
    this->visitLeft = false;
    this->visitRIght = false;
    this->setAllVisted = false;
    this->obstacleFlag = false;
}

/**
 * the constructor.
 * @param p1 - the square points
 */
Square::Square(Point p1) {
    this->point = p1;
    this->numSon =0;
    this->bfsVal =0;
    this->leftSon=NULL;
    this->SetBottom(NULL);
    this->rightSon=NULL;
    this->upperSon=NULL;
    this->visitBottom = false;
    this->visitUp = false;
    this->visitLeft = false;
    this->visitRIght = false;
    this->setAllVisted = false;
    this->obstacleFlag = false;

}

Square::Square() {

}

/**
 * the destructor
 */
Square::~Square(){
    this->bfsVal = 0;
    this->numSon = 0;
    this->visitBottom = false;
    this->visitUp = false;
    this->visitLeft = false;
    this->visitRIght = false;
    this->setAllVisted = false;

}





/**
 * @param b - seting the set all visited variable
 */
void Square::setVisited(bool b) {
    this->setAllVisted = b;
}

/**
 * @param s - set the botoom son
 */
void Square:: SetBottom(Square* s){
    this->bottomSon = s;

}

/**
 * @return - geting the set all visited variable.
 */
bool Square::getVisited() {
    return this->setAllVisted;
}

/**
 * @param b - setting the find on grid bool variable
 */
void Square::setVisitFind(bool b) {
    this->visitToFind = b;
}

/**
 * @param b  - the bfs visit bottom bool
 */
void Square::setVisitB(bool b) {
    this->visitBottom = b;
}

/**
 * @param b   - the bfs visit left bool
 */
void Square::setVisitL(bool b) {
    this->visitLeft = b;
}

/**
 *  @param b  - the bfs visit upper bool
 */
void Square::setVisitU(bool b) {
    this->visitUp = b;
}

/**
 * @param b  - the bfs visit right bool
 */
void Square::setVisitR(bool b) {
    this->visitRIght = b;
}

/**
 * @return -the bfs visit botoom bool
 */
Square *Square::getBotoom() {
    return this->bottomSon;
}

/**
 * @return - the bfs visit right bool
 */
Square *Square::getRight() {
    return this->rightSon;
}

/**
 * @return -the bfs visit left bool
 */
Square *Square::getLeft() {
    return this->leftSon;
}

/**
 * @return -the bfs visit rupper bool
 */
Square *Square::getUpper() {
    return this->upperSon;
}

/**
 * @param a  - the new bfs val
 */
void Square::setBfsVal(int a) {
    this->bfsVal = a;
}

/**
 * @param father - the new bfs father
 */
void Square::setBfsFather(Square *father) {
    this->bfsFather = father;
}

/**
 * @return - the bfs routh father
 */
Square* Square::getBstFather() {
    return this->bfsFather;
}

/**
 * @return - if the square is an obstacle
 */
bool Square::isObstacleFlag() const {
    return obstacleFlag;
}

/**
 * @return - if we visit the left side in the bfs search
 */
bool Square::isVisitLeft() const {
    return visitLeft;
}

/**
 * @return - if we visit the botoom side in the bfs search
 */
bool Square::isVisitBottom() const {
    return visitBottom;
}

/**
 * @return - if we visit the right side in the bfs search
 */
bool Square::isVisitRIght() const {
    return visitRIght;
}

/**
 * @return - if we visit the upper side in the bfs search
 */
bool Square::isVisitUp() const {
    return visitUp;
}

/**
 * setting the squares to be false so we can initialize their vals before abfs run
 */
void Square::setBeforeBfs(std::list<Searchable *> l) {
    for(int i=0;i<l.size();i++){
        Searchable*s = l.front();
        Square* square =(Square*) s;
        square->setAllVisted = false;
        l.pop_front();
        l.push_back(s);
    }
}