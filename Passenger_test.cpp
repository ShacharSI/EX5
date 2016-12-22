
#include <gtest/gtest.h>
#include "Passenger.h"

class Passenger_test: public ::testing::Test{
protected:
    Passenger psngr;
    Point dst;
    Point src;

    virtual void setUp(){
        cout<<"set up";
    }
    virtual void TearDown(){
        cout<<"tearingDown";
    }

public:
    Passenger_test(){
        src = Point(2,3);
        dst = Point(6,7);
        psngr = Passenger("Sam",src,dst);
    }
};

TEST_F(Passenger_test,checkName){
    ASSERT_EQ("Sam",psngr.getName());
}

TEST_F(Passenger_test,checkSrc){
    ASSERT_TRUE(src.equals(psngr.getSrc()));
}

TEST_F(Passenger_test,checkDst){
    ASSERT_TRUE(dst.equals(psngr.getDest()));
}

TEST_F(Passenger_test,checkSatis){
    ASSERT_LE(1,psngr.giveSatis());
    ASSERT_GE(5,psngr.giveSatis());
}