#include <gtest/gtest.h>
#include "MapFactory.h"


/**
 * mapFactoru testing
 */
class Map_Factory_Test: public ::testing::Test {

protected:
    MapFactory mf;


    virtual void setUp(){

    }
    virtual void TearDown(){
        cout<<"tearingDown";
    }

public:
    Map_Factory_Test() {
    }

};

/**
 * checking that the process of creating a map is
 * working well
 */
TEST_F(Map_Factory_Test,testMapCreation){
    std::list<Point> list;
    Map m = this->mf.createMapSearchable("Square",3,3,0,0,list);
    EXPECT_EQ(m.getStart()->getPoint().equals(Point(0,0)),true);
    EXPECT_EQ(9,m.getL().size());
    EXPECT_EQ(m.getL().front()->getPoint().equals(Point(0,0)),true);
}