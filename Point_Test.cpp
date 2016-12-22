//
// Created by haim on 12/16/16.
//



#include "Point.h"
#include <gtest/gtest.h>

/**
 * testing the point class
 */
class Point_Test: public ::testing::Test {

protected:
    Point p1;
    Point p2;

    virtual void setUp(){
        this->p1 = Point(1,2);
        this->p2 = Point(1,2);

    }
    virtual void TearDown(){
        cout<<"tearingDown";
    }

public:
    Point_Test() {
        this->setUp();
    }

};

/**
 * checking the getters
 */
TEST_F(Point_Test,GetFuncTest) {
    EXPECT_EQ(1,this->p1.getX());
    EXPECT_EQ(2,this->p1.getY());
    EXPECT_EQ(true,this->p1.equals(p2));
}

/**
 * checking that the function that is in charge of making sure
 * that the input is correct- is working good
 */
TEST_F(Point_Test,validte){
    Point p(-1,0);
    try {
        p.validate();
    }catch (std::invalid_argument& err){
        ASSERT_STREQ(err.what(),"wrong coordinate");
    }
}

/**
 * checking that the overload printing function is working good
 */
TEST_F(Point_Test,checkPrint){
    testing::internal::CaptureStdout();
    std::cout << p1;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output,"(1,2)\n");
}