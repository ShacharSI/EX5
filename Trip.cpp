//
// Created by haim on 11/27/16.
//

#include <sstream>
#include "Trip.h"
#include <stdexcept>

/**
 * the constructor
 */
Trip::Trip() {

}

/**
 * the constructor
 */
Trip::Trip(int id, int startX,int startY,int endX, int endY,int psgNum, double tarrif) {
    this->endP = Point(endX,endY);
    this->id = id;
    this->passengersNum = psgNum;
    this->startP = Point(startX,startY);
    this->taarif = tarrif;
    this->passedMeter = 0;
}

/**
 * checking that the trip' info is good and make sense
 */
void Trip::validate() {
    if((this->getId() < 0)||(this->getStartP().getX() < 0)||(this->getStartP().getY()<0) ||(this->passengersNum < 0)||
       (this->taarif <0)||(this->getEndP().getX() < 0)||(this->getEndP().getY() <0)){
        throw invalid_argument("wrong trip data");
    }
}
/**
 * @return - the trip's distance
 */
int Trip::getDistance() {
    return 0;
}

/**
 * @return - the trip's passed meters
 */
int Trip::getPassedMeter() {
    return 0;
}

/**
 * @return - the trip's id
 */
int Trip::getId() {
    return id;
}



/**
 * @return - the trip's tarrif
 */
double Trip::getTaarif()  {
    return taarif;
}

/**
 * @return - the trip's start point
 */
Point Trip::getStartP()  {
    return startP;
}

/**
 * @return - the trip's end
 */
Point Trip::getEndP()  {
    return endP;
}
