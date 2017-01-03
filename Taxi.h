#ifndef TM_TAXI_H
#define TM_TAXI_H

#include <vector>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include "Point.h"
#include "Passenger.h"
#include "Trip.h"
#include "Bfs.h"
#include "Map.h"

/**
 * a class that represent a taxi
 */
class Taxi : public Vallidate_Interface {
public:
    typedef enum {
        HONDA, SUBARO, TESLA, FIAT
    } manufacturer;
    typedef enum {
        RED, BLUE, GREEN, PINK, WHITE
    } color;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Vallidate_Interface>(*this);
        ar & carId;
        ar & mnfctr;
        ar & clr;
        ar & tarrif;
        ar & location;
    }

    void validate();

    static manufacturer parseMnfctr(string s);

    static color parseColor(string s);

    Taxi();

    ~Taxi();

    Taxi(int idNum, manufacturer mnfctr, color clr, int taarif);

    Point getLocation();

    void setLocation(Point newLocation);

    int getTarrif();

    void addPassengers(vector<Passenger> psngrs);

    int getCarId() const;

    manufacturer getMnfctr() const;

    color getClr() const;

    virtual void move() = 0;

    bool operator==(const Taxi &other) {
        return this->carId == other.carId && this->mnfctr == other.mnfctr && this->clr == other.clr
               && this->tarrif == other.tarrif;
    }

    vector<Passenger> getPassengers();

    void setRouth(list<Searchable *> routhFromClientToDes);

    list<Searchable *> getRouth();

protected:
    list<Searchable *> routh;
    int carId;
    manufacturer mnfctr;
    int tarrif;
    color clr;
    Point location;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Taxi)

#endif //TM_TAXI_H