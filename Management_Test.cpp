
#include <gtest/gtest.h>
#include "Management.h"
#include "StandardTaxi.h"

class Management_Test : public ::testing::Test {

protected:


    virtual void setUp() {

    }

    virtual void TearDown() {


    }

public:
    Management_Test() {
    }

};


/*
 * checking that parsing a driver from string is working
 */
TEST_F(Management_Test,driverParse){
    Management m;
    string d = "0,30,M,1,0";
    Driver* driver = m.parseDriver(d);
    EXPECT_EQ(driver->getAge(),30);
    EXPECT_EQ(driver->getId(),0);
    EXPECT_EQ(driver->getExpYears(),1);
    EXPECT_EQ(driver->getVehicle_id(),0);
    delete(driver);

}

/*
 * checking that parsing a taxi from string is working
 */
TEST_F(Management_Test,texiParse){
    Management m;
    string d = "0,1,H,G";
    Taxi* t = m.parseTaxi(d);
    EXPECT_EQ(t->getCarId(),0);
    EXPECT_EQ(t->getTarrif(),1);
    delete(t);
}

/*
 * checking that parsing a trip from string is working
 */
TEST_F(Management_Test,tripParse){
    Management m;
    string s = "0,0,0,0,2,1,20";
    Trip t = m.parseTrip(s);
    EXPECT_EQ(t.getStartP().getX(),0);
    EXPECT_EQ(t.getStartP().getY(),0);
    EXPECT_EQ(t.getId(),0);
    EXPECT_EQ(t.getEndP().getX(),0);
    EXPECT_EQ(t.getEndP().getY(),2);
}