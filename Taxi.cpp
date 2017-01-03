//
// Created by haim on 11/27/16.
//

#include "Taxi.h"
#include <boost/foreach.hpp>
#include "Driver.h"
#include <stdexcept>

/**
 * @return - the taxi'x location
 */
Point Taxi::getLocation() {
    return this->location;
}

/**
 * @return - the taxi'x tarrif
 */
int Taxi::getTarrif() {
    return this->tarrif;
}

/**
 * update the taxi's location
 */
void Taxi::setLocation(Point newLocation) {
    this->location = newLocation;
}

/**
 * the constructor
 */
Taxi::Taxi() {

}

/**
 * the deconstructor
 */
Taxi::~Taxi() {

}

/**
 * the construtor
 */
Taxi::Taxi(int id, Taxi::manufacturer mntrf, Taxi::color color,int taarif) {
    this->carId = id;
    this->tarrif = taarif;
    this->clr = color;
    this->mnfctr = mntrf;
    std::list<Searchable*> l1;
    this->routh = l1;

}
/**
 *
 * @return - the taxi's id
 */
int Taxi::getCarId() const {
    return this->carId;
}

/**
 *
 * @return - the taxi's manufactur
 */
Taxi::manufacturer Taxi::getMnfctr() const {
    return this->mnfctr;
}

/**
 *
 * @return - the taxi's color
 */
Taxi::color Taxi::getClr() const {
    return this->clr;
}

/**
 * add a passenger to the taxi
 */
void Taxi::addPassengers(vector<Passenger> psngrs) {

}

/**
 * 
 * get the taxi's passenger
 */
vector<Passenger> Taxi::getPassengers() {
    return vector<Passenger>();
}

/**
 * set thr taxi's routh to the next location
 */
void Taxi::setRouth(std::list < Searchable * > routhToLocation) {
    this->routh = routhToLocation;

}

/**
 * get the routh to the destiny
 */
list<Searchable *> Taxi::getRouth() {
    return this->routh;
}

/**
 * get a string and parse a manufactur from it
 */
Taxi::manufacturer Taxi::parseMnfctr(string s) {
    switch (s[0]){
        case 'H':
            return HONDA;
        case 'S':
            return SUBARO;
        case 'T':
            return TESLA;
        case 'F':
            return FIAT;
        default:
            break;

    }
    throw invalid_argument("wrong input");
}

/**
 * get a string and parse a color fom it
 */
Taxi::color Taxi::parseColor(string s) {
    switch (s[0]){
        case 'R':
            return RED;
        case 'B':
            return BLUE;
        case 'P':
            return PINK;
        case 'G':
            return GREEN;
        case 'W':
            return WHITE;
        default:
            break;

    }
    throw invalid_argument("wrong input");
}

/**
 * make sure that the taxi was created from valid input
 */
void Taxi::validate() {

    if(this->getCarId() < 0||(this->tarrif < 0)){
        throw invalid_argument("wrong input");
    }
}