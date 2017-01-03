//
// Created by haim on 11/27/16.
//

#ifndef TM_SSTNDTAXIFACTORY_H
#define TM_SSTNDTAXIFACTORY_H


#include <boost/serialization/nvp.hpp>
#include "VirtualTaxiFactory.h"
#include "Taxi.h"

/**
 * a class that is in charge of creating a stnd taxi
 */
class StndTaxiFactory: public VirtualTaxiFactory {

public:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Taxi);
    }
    StndTaxiFactory();
    Taxi* createTaxi(int id, Taxi::manufacturer mntrf, Taxi::color color);
    StndTaxiFactory(int taarif);

private:
    int taarif;
};

#endif //TM_SSTNDTAXIFACTORY_H