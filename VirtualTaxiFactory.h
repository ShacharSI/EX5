//
// Created by haim on 11/27/16.
//

#ifndef TM_VIRTUALTAXIFACTORY_H
#define TM_VIRTUALTAXIFACTORY_H


#include "Taxi.h"

class VirtualTaxiFactory {
private:
    //check
    int tarrif;
    int a;
public:
    virtual Taxi* createTaxi(int id, Taxi::manufacturer mntrf, Taxi::color color)=0;
    VirtualTaxiFactory(int taarif);
    VirtualTaxiFactory();
};


#endif //TM_VIRTUALTAXIFACTORY_H