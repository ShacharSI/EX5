
#include <gtest/gtest.h>
#include "Point.h"
#include "Square.h"
#include "Map.h"

/**
 * testing the map class
 */
class Map_Tesr: public ::testing::Test {

protected:


    virtual void setUp(){

    }
    virtual void TearDown(){
        cout<<"tearingDown";

    }

public:
    Map_Tesr() {
    }

};

/**
 * cheking that all the functions in the map class
 * is working good
 */
TEST_F(Map_Tesr,checkMap){
    Square* square =new Square(0,0);
    Square* s = new Square(2,3); // todo delete is not working  how??????
    std::list<Searchable*> l;
    Searchable* s1 = s;
    l.push_back(s1);
    Map m(2,2,square,l);
    Point p = m.getStart()->getPoint();
    ASSERT_EQ(p.equals(Point(0,0)), true);
    m.freeAll();
    ASSERT_EQ(0,m.getL().size());
    delete square;
    //delete s;
}