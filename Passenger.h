//
// Created by haim on 11/27/16.
//

#ifndef TM_PASSENGER_H
#define TM_PASSENGER_H


#include "Point.h"
/**
 * a class that represent a taxi passenger
 */
class Passenger {
private:
    string name;
    Point src;
    Point dest;
public:
    bool operator==(const Passenger &other) const{
        return this->name == other.name && this->src.equals(other.src) &&this->dest.equals(other.dest);
    }
    string getName();
    Point getSrc();
    Point getDest();
    Passenger();
    Passenger(string name,Point source,Point destination);
    int giveSatis();
};


#endif //TM_PASSENGER_H