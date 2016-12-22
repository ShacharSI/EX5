

#ifndef TM_LUXTAXIFACTORY_H
#define TM_LUXTAXIFACTORY_H


#include "Taxi.h"
#include "VirtualTaxiFactory.h"

/**
 * a class that is in charge of creating a luxury taxi with the matching taarif
 */
class LuxTaxiFactory: public VirtualTaxiFactory {
private:
    int tarrif;
public:
    LuxTaxiFactory();
    LuxTaxiFactory(int taarif);
    Taxi* createTaxi(int id, Taxi::manufacturer mntrf, Taxi::color color);
};


#endif //TM_LUXTAXIFACTORY_H