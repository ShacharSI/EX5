//
// Created by haim on 11/27/16.
//

#include "StndTaxiFactory.h"
#include "StandardTaxi.h"

/**
 * create a new matching taxi
 */
Taxi* StndTaxiFactory::createTaxi(int id, Taxi::manufacturer mntrf, Taxi::color color) {
    Taxi *taxi = new StandardTaxi(id, mntrf, color, this->taarif);
    return taxi;
}

/**
 * the constructor
 */
StndTaxiFactory::StndTaxiFactory() {
}

/**
 * the constructor
 */
StndTaxiFactory::StndTaxiFactory(int taarif):VirtualTaxiFactory(taarif) {
    this->taarif = taarif;
}