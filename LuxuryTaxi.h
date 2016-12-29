//
// Created by haim on 11/27/16.
//

#ifndef TM_LUXURYTAXI_H
#define TM_LUXURYTAXI_H


#include "Taxi.h"

/**
 * a class that represent a luxury taxi that moves faster and have different taarif
 */
class LuxuryTaxi: public Taxi {

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Taxi>(*this);
    }
public:
    void move();
    LuxuryTaxi();
    LuxuryTaxi(int idNum,manufacturer mnfctr, color clr,int taarif);
};


#endif //TM_LUXURYTAXI_H