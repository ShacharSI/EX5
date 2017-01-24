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
Trip::Trip(int id, int starX,int starY,int enX, int enY,int psgNum, double tarrif, unsigned int t) {
    this->endP = Point(enX,enY);
    this->id = id;
    this->passengersNum = psgNum;
    this->startP = Point(starX,starY);
    this->taarif = tarrif;
    this->startX = starX;
    this->startY =starY;
    this->endX = enX;
    this->endY = enY;
    this->passedMeter = 0;
    this->time = t;
}

/**
 * checking that the trip' info is good and make sense
 */
int Trip::validate() {
    if((this->getId() < 0)||(this->getStartP().getX() < 0)||(this->getStartP().getY()<0) ||(this->passengersNum < 0)||
       (this->taarif <0)||(this->getEndP().getX() < 0)||(this->getEndP().getY() <0)||(this->time<=0)){
        return -1;
    }
    return 0;
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

/**
 * @return - the time of the trip to activte
 */
unsigned int Trip::getTime() {
    return this->time;
}

Trip::~Trip() {

}