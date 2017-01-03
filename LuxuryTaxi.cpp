//
// Created by haim on 11/27/16.
//

#include "LuxuryTaxi.h"

/**
 * the empty constructor
 */
LuxuryTaxi::LuxuryTaxi() {

}

/**
 * the constructor
 */
LuxuryTaxi::LuxuryTaxi(int idNum, manufacturer mnfctr, color clr, int taarif) :
        Taxi(idNum, mnfctr, clr, taarif) {
}

/**
 * move the taxi to the new location
 */
void LuxuryTaxi::move() {
    if(this->routh.size() > 2){
        this->routh.pop_front();
        this->routh.pop_front();
        Point p = this->routh.front()->getPoint();
        this->location = p;
        return;
    } if(this->routh.size() == 1){
        Point p = this->routh.front()->getPoint();
        this->routh.pop_front();
        return;
    } if(this->routh.size() == 2){
        this->routh.pop_front();
        Point p = this->routh.front()->getPoint();
        this->location = p;
        this->routh.pop_front();
        return;
    }

}

