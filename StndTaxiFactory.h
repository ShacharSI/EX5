//
// Created by haim on 11/27/16.
//

#ifndef TM_SSTNDTAXIFACTORY_H
#define TM_SSTNDTAXIFACTORY_H


#include "VirtualTaxiFactory.h"
#include "Taxi.h"

class StndTaxiFactory: public VirtualTaxiFactory {

public:
    StndTaxiFactory();
    Taxi* createTaxi(int id, Taxi::manufacturer mntrf, Taxi::color color);
    StndTaxiFactory(int taarif);

private:
    int taarif;
};

#endif //TM_SSTNDTAXIFACTORY_H