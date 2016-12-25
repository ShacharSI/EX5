

#ifndef TM_TAXI_H
#define TM_TAXI_H


#include <vector>
#include "Point.h"
#include "Passenger.h"
#include "Trip.h"
#include "Bfs.h"
#include "Map.h"

class Taxi : public Vallidate_Interface {
public:
    typedef enum {
        HONDA, SUBARO, TESLA, FIAT
    } manufacturer;
    typedef enum {
        RED, BLUE, GREEN, PINK, WHITE
    } color;

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

    list<Searchable *> calculateBfs(Point start, Point end);

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

    Map getMap();

    void setMap(Map m);

    list<Searchable *> getRouth();

protected:
    list<Searchable *> routh;
    Map map;
    int carId;
    manufacturer mnfctr;
    Trip trip;
    int tarrif;
    Algorithm* searchAlgo;
    color clr;
    Point location;

};


#endif //TM_TAXI_H