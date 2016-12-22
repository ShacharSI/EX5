//
// Created by haim on 11/27/16.
//

#include "Passenger.h"
#include <cstdlib>

/**
 * the constructor
 */
Passenger::Passenger() {

}

/**
 * the constructor
 */
Passenger::Passenger(string name, Point source, Point destination) {
    this->dest = destination;
    this->name = name;
    this->src = source;
}

/**
 * @return  - the passenger satisfaction from the driver
 */
int Passenger::giveSatis() {
    return rand()%5 + 1;
}

/**
 * @return  - the passenger name
 */
string Passenger::getName() {
    return this->name;
}

/**
 * @return  - the passenger source trip point
 */
Point Passenger::getSrc()  {
    return this->src;
}

/**
 * @return  - the passenger destination trip point
 */
Point Passenger::getDest()  {
    return this->dest;
}