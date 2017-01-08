

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
 * the constructor.
 * @param x - the square x coordinade
 * @param y -  the square y coordinade
 */
Square::Square(int x, int y) {
    Point p(x, y);
    this->point = p;
    this->setAllVisted = false;

}

/**
 * the constructor.
 * @param p1 - the square points
 */
Square::Square(Point p1) {
    this->point = p1;
}

Square::Square() {

}

/**
 * the destructor
 */
Square::~Square(){
}

Searchable *Square::getFather() {
    return this->bfsFather;
}

bool Square::getBfsVisited() {
    return this->bfsVisited;
}



bool Square::setBfsVisited(bool b) {
    this->bfsVisited = b;
}

void Square::setBfsFather(Searchable *s) {
    this->bfsFather = (Square*)s;
}

bool Square::isObstacle() {
    return this->bfsVisited;
}

void Square::setObstacle(bool b) {
    this->obstacle = b;
}
