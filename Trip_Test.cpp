#include <gtest/gtest.h>
#include "Trip.h"
#include "LuxuryTaxi.h"


/**
 * testing the trip class
 */
class Trip_Test: public ::testing::Test {

protected:
    Trip t;


    virtual void setUp(){

    }
    virtual void TearDown() {
    }

public:
    Trip_Test() {

        t=Trip(12,0,0,3,2,2,2);
    }

};

/**
 * checking the getters
 * and the creation of the class
 */
TEST_F(Trip_Test,checkGetters){
    EXPECT_EQ(12,t.getId());
    EXPECT_EQ(2,t.getTaarif());
    EXPECT_EQ(t.getDistance(),0);
    Point p = t.getStartP();
    EXPECT_EQ(p.equals(Point(0,0)), true);
    p= t.getEndP();
    EXPECT_EQ(p.equals(Point(3,2)), true);

}