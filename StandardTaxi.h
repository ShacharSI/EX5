//
// Created by haim on 11/27/16.
//

#ifndef TM_STANDARDTAXI_H
#define TM_STANDARDTAXI_H


#include "Taxi.h"

class StandardTaxi: public Taxi {

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Taxi>(*this);
    }
public:
    void move();
    StandardTaxi();
    StandardTaxi(int idNum,manufacturer mnfctr, color clr,int taarif);

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Taxi>(*this);
    }
};

#endif //TM_STANDARDTAXI_H