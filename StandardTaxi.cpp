//
// Created by haim on 11/27/16.
//

#include "StandardTaxi.h"

StandardTaxi::StandardTaxi() {

}

StandardTaxi::StandardTaxi(int idNum,manufacturer mnfctr, color clr,int taarif):
        Taxi(idNum,mnfctr,clr,taarif) {
}

void StandardTaxi::move() {

    
    if(this->routh.size() > 0){
        this->location =this->routh.front()->getPoint();
        this->routh.pop_front();
    }
    
    Point p = this->routh.front()->getPoint();
    this->location = p;
}