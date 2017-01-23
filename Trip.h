//
// Created by haim on 11/27/16.
//

#ifndef TM_TRIP_H
#define TM_TRIP_H


#include <vector>
#include <boost/serialization/access.hpp>
#include "Point.h"
#include "Passenger.h"
/**
 * a class that represent a trip(recived as a request by the user-passenger)
 */
class Trip{
private:
    int id;
    int distance;
    double taarif;
    int passedMeter;
    long passengersNum;
    int startX;
    int startY;
    int endX;
    int endY;
    Point startP;
    Point endP;
    unsigned int time;
public:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & startX;
        ar & startY;
        ar & endX;
        ar & endY;
        ar & passengersNum;
        ar & taarif;
        ar & time;
    }
    int validate();
    int getId();
    double getTaarif() ;
    int getDistance();
    Point getStartP();
    Point getEndP() ;
    int getPassedMeter();
    Trip();
    unsigned int getTime();
    Trip(int id, int startX,int startY,int endX, int endY,int psgNum, double tarrif, unsigned int time);
    ~Trip();
};


#endif //TM_TRIP_H