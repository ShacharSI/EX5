//
// Created by haim on 11/27/16.
//

#ifndef TM_TRIP_H
#define TM_TRIP_H


#include <vector>
#include "Point.h"
#include "Passenger.h"
/**
 * a class that represent a trip(recived as a request by the user-passenger)
 */
class Trip: public Vallidate_Interface {
private:
    int id;
    int distance;
    double taarif;
    int passedMeter;
    long passengersNum;
    Point startP;
    Point endP;
public:
    void validate();
    int getId();
    double getTaarif() ;
    int getDistance();
    Point getStartP();
    Point getEndP() ;
    int getPassedMeter();
    Trip();
    Trip(int id, int startX,int startY,int endX, int endY,int psgNum, double tarrif);

};


#endif //TM_TRIP_H