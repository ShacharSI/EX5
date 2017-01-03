//
// Created by haim on 11/27/16.
//

#include "StandardTaxi.h"

/**
 * the constructor
 */
StandardTaxi::StandardTaxi() {

}

/**
 * the constructor
 */
StandardTaxi::StandardTaxi(int idNum,manufacturer mnfctr, color clr,int taarif):
        Taxi(idNum,mnfctr,clr,taarif) {
}

/**
 * moving the taxi to the next location
 */
void StandardTaxi::move() {
    if(this->routh.size() > 1){ //todo fix also in luxury
        this->routh.pop_front();
        Point p = this->routh.front()->getPoint();
        this->location = p;
        return;
    } if(this->routh.size() == 1){
        this->routh.pop_front();
    }
}

/**
 * the deconstructor
 */
StandardTaxi::~StandardTaxi() {

}
