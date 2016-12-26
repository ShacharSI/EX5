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
 * move the taxi to location
 */
void LuxuryTaxi::move() {

    if (this->routh.size() > 0) {
        this->location = this->routh.front()->getPoint();
        this->routh.pop_front();
        if (this->routh.size() > 0) {
            this->location = this->routh.front()->getPoint();
            this->routh.pop_front();
        }
    }
    Point p = this->routh.front()->getPoint();
    this->location = p;
}

