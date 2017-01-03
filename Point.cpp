#include "Point.h"
#include <stdexcept>

/**
 * the constructor.
 *
 * @param num1 - x coordinate
 * @param num2 - y coordinate
 */
Point::Point(int num1, int num2){
    this->x =num1;
    this->y =num2;
}

/**
 * empty constructor
 */
Point::Point(){
}

/**
 * the destructor
 */
Point::~Point() {

}

/**
 * make sure that the point was created from valid input
 */
void Point::validate() {
    if ((this->x< 0)||(this->y <0)){
        throw invalid_argument("wrong coordinate");
    }
}

/**
 * checking if a point equals to another point
 *
 * @param p - the other point
 * @return  - true if equals.
 */
bool Point::equals(Point p) const{
    return ((this->x == p.getX()) &&  (this->y == p.getY()));
}

/**
 * @return - the x coordinate
 */
int Point::getX() {
    return this->x;
}

/**
 * @return - the y coordinate
 */
int Point::getY() {
    return this->y;
}