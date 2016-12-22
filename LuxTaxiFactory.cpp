//
// Created by sha on 12/4/16.
//

#include "LuxTaxiFactory.h"
#include "LuxuryTaxi.h"

/**
 * the empty constructor
 */
LuxTaxiFactory::LuxTaxiFactory() {

}

/**
 * the constructor
 */
LuxTaxiFactory::LuxTaxiFactory(int taarif) {
    this->tarrif = taarif;
}

/**
 * create a taxi with given info
 */
Taxi* LuxTaxiFactory::createTaxi(int id, Taxi::manufacturer mntrf, Taxi::color color) {
    Taxi* taxi = new LuxuryTaxi(id,mntrf,color,this->tarrif);
    return taxi;
}