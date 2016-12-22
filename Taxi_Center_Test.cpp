//
// Created by haim on 12/16/16.
//


#include <gtest/gtest.h>
#include "TaxiCenter.h"
#include "MapFactory.h"
#include "StandardTaxi.h"
#include "Logic.h"

/**
 * testing the taxi center
 */
class Taxi_Center_Test: public ::testing::Test{


protected:


    virtual void setUp(){

    }
    virtual void TearDown(){

    }

public:
    Taxi_Center_Test() {
    }
};

/**
 * checking the setters
 */
TEST_F(Taxi_Center_Test,checkSetters){ std::list<Point> list;
    vector<int> v;
    v.push_back(3);
    v.push_back(3);
    Logic logic(v);
    logic.setObstacle(0);
    TaxiCenter taxiCenter(logic.createNewMap("Square"));
    Driver* d1 = new Driver (12,22,Driver:: martialStatus::DIVORCED,1,13);
    taxiCenter.setNotActiveDriver(d1);
}



/**
 * checking that the taxi_center is giving back the
 * current location of a taxi
 */
TEST_F(Taxi_Center_Test,checkGetLocation){
    MapFactory mf;
    std::list<Point> list;
    Map m = mf.createMapSearchable("Square",3,3,0,0,list);
    TaxiCenter taxiCenter(m);
    Driver* d = new Driver(12,22,Driver:: martialStatus::MARRIED,1,14);
    Taxi* t = new StandardTaxi(14,Taxi::FIAT,Taxi::BLUE,1);
    t->setLocation(Point(0,0));
    d->setTaxi(t);
    taxiCenter.addDriverToCenter(d);
    Point p2 = taxiCenter.giveLocation(14);
    EXPECT_EQ(p2.equals(Point(0,0)),true);

}

/**
 * checking that the function that recives a call
 * is working well
 */
TEST_F(Taxi_Center_Test,checkCall){
    MapFactory mf;
    std::list<Point> list;
    Map m = mf.createMapSearchable("Square",3,3,0,0,list);
    TaxiCenter taxiCenter(m);
    Trip c(13,0,0,4,15,2,1);
    try {
        taxiCenter.setTrip(c);
    }catch (std::invalid_argument& err){
        EXPECT_STREQ(err.what(),"invalid location");
    }

}