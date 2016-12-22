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

    if (this->routhFromLocationToClient.size() > 0) {
        this->location = this->routhFromLocationToClient.front()->getPoint();
        this->routhFromLocationToClient.pop_front();
        if (this->routhFromLocationToClient.size() > 0) {
            this->location = this->routhFromLocationToClient.front()->getPoint();
            this->routhFromLocationToClient.pop_front();
        }
        return;
    }
    if (this->routhFromClientToDes.size() > 0) {
        this->location = this->routhFromClientToDes.front()->getPoint();
        this->routhFromClientToDes.pop_front();
        if (this->routhFromClientToDes.size() > 0) {
            this->location = this->routhFromClientToDes.front()->getPoint();
            this->routhFromClientToDes.pop_front();
        }
    }
}

