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

    /*if(this->routhFromLocationToClient.size() > 0){
        this->location =this->routhFromLocationToClient.front()->getPoint();
        this->routhFromLocationToClient.pop_front();
        return;
    }
    if(this->routhFromClientToDes.size() > 0){
        this->location =this->routhFromClientToDes.front()->getPoint();
        this->routhFromClientToDes.pop_front();
    }*/
    Point p;

    p = this->routhFromClientToDes.front()->getPoint();
    this->location = p;
}