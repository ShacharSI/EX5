//
// Created by haim on 11/27/16.
//

#include <sstream>
#include "Driver.h"
#include <stdexcept>


/**
 * the destructor
 */
Driver::~Driver() {
    if (this->taxi != NULL) {
        delete this->taxi;
    }
}

/*
 * the empty constructor
 */
Driver::Driver() {

}

/**
 * the connstructor
 */
Driver::Driver(int idNum, int ag, Driver::martialStatus martialStatus, int expY, int vehicle_ide) {
    this->age = ag;
    this->expYears = expY;
    this->id = idNum;
    this->martialStat = martialStatus;
    this->satisCounter = 0;
    this->averageSatisfaction = 0;
    this->vehicle_id = vehicle_ide;
    this->taxi = NULL;
}

/**
 * @return - the driver id
 */
int Driver::getId() {
    return this->id;
}

/**
 * assign a taxi to the driver
 * @param t - the taxi
 */
void Driver::setTaxi(Taxi *t) {
    this->taxi = t;
}

/**
 * @param newSatis - the driver satisfaction from client
 */
void Driver::updateSatis(int newSatis) {
    double newSatisSum = (this->averageSatisfaction * this->satisCounter) + newSatis;
    this->satisCounter++;
    this->averageSatisfaction = newSatisSum / satisCounter;

}

/**
 * @return - the drivers experience
 */
int Driver::getExpYears() {
    return this->expYears;
}

/**
 * @return - the drivers age
 */
int Driver::getAge() {
    return this->age;
}

/**
 * @return - the drivers taxi
 */
Taxi *Driver::getTaxi() const {
    return taxi;
}

/**
 * make shure that the drivers info are logical ang correct
 */
void Driver::validate() {
    if ((this->getAge() < 0) || (this->getExpYears() < 0) || (this->getId() < 0)) {
        throw invalid_argument(" wrong driver input");
    }
}

/**
 * @return - the drivers location
 */
Point Driver::getLocation() {
    return this->taxi->getLocation();
}


/**
 * movs the driver around
 */
void Driver::move() {
    this->taxi->move();
}

/**
 * @return - the drivers vehicle id
 */
int Driver::getVehicle_id() {
    return vehicle_id;
}

/**
 * getting a letter and parsing it into a martial status
 * @return - the martial status
 */
Driver::martialStatus Driver::parseMartialStatus(string martialStatus) {
    switch (martialStatus[0]) {
        case 'W':
            return WIDOWED;
        case 'D':
            return DIVORCED;
        case 'S':
            return SINGLE;
        case 'M':
            return MARRIED;
        default:
            break;
    }
}

/**
 * @return - the driver's satisfaction
 */
double Driver::getSatis() {
    return this->averageSatisfaction;
}

/**
 * when the trip ends tive the driver
 * remove from active list and put in not active list
 */
void Driver::inactivate(std::list<Driver *> &inActDrivers, list<Driver *> &actDrivers) {
    Driver *d;
    for (int i = 0; i < actDrivers.size(); ++i) {
        d = actDrivers.front();
        if (d->getId() == this->id) {
            actDrivers.pop_front();
            break;
        }
        actDrivers.pop_front();
        actDrivers.push_back(d);
    }
    inActDrivers.push_back(d);
}

/**
 * @param list - set the routh
 */
void Driver::setRouth(std::list<Searchable *> list) {
    this->getTaxi()->setRouth(list);
}



