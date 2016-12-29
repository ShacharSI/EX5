//
// Created by haim on 11/27/16.
//

#include "Taxi.h"
#include <boost/foreach.hpp>
#include "Driver.h"
#include <stdexcept>

Point Taxi::getLocation() {
    return this->location;
}

int Taxi::getTarrif() {
    return this->tarrif;
}

void Taxi::setLocation(Point newLocation) {
    this->location = newLocation;
}


Taxi::Taxi() {

}

Taxi::~Taxi() {
    if(this->searchAlgo!=NULL){
        delete this->searchAlgo;
    }
}

Taxi::Taxi(int id, Taxi::manufacturer mntrf, Taxi::color color,int taarif) {
    this->carId = id;
    this->tarrif = taarif;
    this->clr = color;
    this->mnfctr = mntrf;
    this->searchAlgo = new Bfs;
    std::list<Searchable*> l1;
    this->routh = l1;
    this->searchAlgo =NULL;

}

int Taxi::getCarId() const {
    return this->carId;
}

Taxi::manufacturer Taxi::getMnfctr() const {
    return this->mnfctr;
}

Taxi::color Taxi::getClr() const {
    return this->clr;
}

list<Searchable*> Taxi::calculateBfs(Point startP,Point endP) {
   // Searchable* s = this->getMap().getStart();
   // Searchable* start = s->findOnGrid(startP);
   // Searchable* end = s->findOnGrid(endP);
    std::list<Searchable*> list;
   // list = this->bfs.findRouth(start,end);
    /*if(start->getPoint().equals(end->getPoint())){
        list.push_back(start);
    } else{
        list.push_back(start);
        list.push_back(end);
    }*/
    return list;
}

void Taxi::addPassengers(vector<Passenger> psngrs) {

}

vector<Passenger> Taxi::getPassengers() {
    return vector<Passenger>();
}


void Taxi::setRouth(std::list < Searchable * > routhToLocation) {
    this->routh = routhToLocation;

}

Map Taxi::getMap() {
    return this->map;
}

void Taxi::setMap(Map m) {
    this->map = m;
}

list<Searchable *> Taxi::getRouth() {
    return this->routh;
}

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

void Taxi::validate() {

    if(this->getCarId() < 0||(this->tarrif < 0)){
        throw invalid_argument("wrong input");
    }
}