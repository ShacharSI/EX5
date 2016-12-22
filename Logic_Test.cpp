


#include <gtest/gtest.h>
#include "Logic.h"

/**
 * testing the logic class
 */
class Logic_Test: public ::testing::Test{


protected:

    virtual void setUp(){

    }
    virtual void TearDown(){

    }

public:
    Logic_Test() {
    }
};

/**
 * checking that the proccess of parsing a string
 * to numbers is going well
 * also checking the getters
 */
TEST_F(Logic_Test,checkParser){
    std::vector<int> v;
    v.push_back(3);
    v.push_back(3);
    Logic l(v);
    EXPECT_EQ(l.getSizeX(),3);
    EXPECT_EQ(l.getSizeY(),3);
    std::list<Point> list;
    Map map = l.createNewMap("Square");
    Point p = map.getStart()->getPoint();
    ASSERT_EQ(p.equals(Point(0,0)),true);
}

/**
 * checking that the proccess of checking the values given by the user
 * is going well
 */
TEST_F(Logic_Test,validate1){
    std::vector<int> v;
    v.push_back(-1);
    v.push_back(3);
    Logic l(v);
    try {
        l.validate();
    }catch (std::invalid_argument& err){
        ASSERT_STREQ(err.what(),"wrong size");
    }
}

