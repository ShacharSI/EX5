
#ifndef TM_DRIVER_H
#define TM_DRIVER_H


#include "Map.h"
#include "Taxi.h"


class Driver : public Vallidate_Interface {
public:
    typedef enum {
        SINGLE, MARRIED, DIVORCED, WIDOWED
    } martialStatus;

    Driver(int idNum, int ag, martialStatus martialStatus, int expY, int vehicle_id);
    Taxi *getTaxi() const;

    Driver();

    ~Driver();

    void manage();

    void setTaxi(Taxi *t);

    int getId();

    void inactivate(list<Driver *> &inActDrivers, list<Driver *> &actDrivers);

    void move();

    Point getLocation();

    void updateSatis(int newSatis);

    int getExpYears();

    int getAge();

    double getSatis();

    list<Searchable*> calculateBfs(Point start,Point end);

    void setRouth(std::list<Searchable *> list);

    void validate();

    int getVehicle_id();

    bool operator==(const Driver &other) {
        return this->id == other.id;
    }

    static martialStatus parseMartialStatus(string martialStatus);

private:
    int id;
    int age;
    int vehicle_id;
    int expYears;
    double averageSatisfaction;
    int satisCounter;
    martialStatus martialStat;
    Taxi *taxi;

};


#endif //TM_DRIVER_H