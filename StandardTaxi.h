//
// Created by haim on 11/27/16.
//

#ifndef TM_STANDARDTAXI_H
#define TM_STANDARDTAXI_H


#include "Taxi.h"

class StandardTaxi: public Taxi {
public:
    void move();
    StandardTaxi();
    StandardTaxi(int idNum,manufacturer mnfctr, color clr,int taarif);

};


#endif //TM_STANDARDTAXI_H