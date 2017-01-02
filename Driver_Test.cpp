
#include <gtest/gtest.h>
#include "Map.h"
#include "Taxi.h"
#include "Driver.h"
#include "StandardTaxi.h"
#include "LuxuryTaxi.h"

class Driver_Test: public ::testing::Test {
protected:
    Driver d;

    virtual void setUp() {
        cout<<"Set up";
    }

    virtual void TearDown(){
        cout<<"tearingDown";
        delete d;
    }

public:
    Driver_Test(){
        int id = 1;
        int age = 30;
        int expYears = 5;
        Driver::martialStatus martialStatus = Driver::martialStatus::MARRIED;
        d = Driver(id,age,martialStatus,expYears,12);
    }
};

TEST_F(Driver_Test,checkTaxiSetter) {
    Taxi* taxi = new StandardTaxi(3,Taxi::TESLA,Taxi::RED,30);
    d.setTaxi(taxi);
    EXPECT_EQ(taxi,d.getTaxi());
    delete taxi;
}

TEST_F(Driver_Test,checkSatisUpdate) {
    d.updateSatis(5);
    d.updateSatis(3);
    ASSERT_EQ(4,d.getSatis()); //todo check test !!
}

TEST_F(Driver_Test,checkGetID) {
    ASSERT_EQ(1,d.getId());
}

TEST_F(Driver_Test,checkGetAge) {
    ASSERT_EQ(30,d.getAge());
}

TEST_F(Driver_Test,checkGetExp) {
    ASSERT_EQ(5,d.getExpYears());

}

TEST_F(Driver_Test,checkLocation){
    Taxi* t = new LuxuryTaxi(1,Taxi::HONDA,Taxi::GREEN,1);
    t->setLocation(Point(0,1));
    d.setTaxi(t);
    EXPECT_EQ(d.getLocation().equals(Point(0,1)), true);
    delete t;
}

TEST_F(Driver_Test,inactiveTest){
    std::list<Driver*> l1;
    std::list<Driver*>l2;
    Driver* drive = new Driver(0,24,Driver::MARRIED,3,2);
    EXPECT_EQ(l1.size(),0);
    EXPECT_EQ(l2.size(),0);
    l1.push_back(drive);
    EXPECT_EQ(l1.size(),1);
    drive->inactivate(l2,l1);
    EXPECT_EQ(l2.size(),1);
    delete drive;
}

TEST_F(Driver_Test,moveTest){
    Taxi* t = new StandardTaxi(3,Taxi::TESLA,Taxi::RED,30);
    d.setTaxi(t);
    std::list<Searchable*> list;
    Searchable* s = new Square(0,0);
    Searchable* s1 = new Square(2,3);
    list.push_back(s1);
    list.push_back(s);
    t->setRouth(list);
    d.move();
    EXPECT_EQ(d.getLocation().equals(Point(2,3)), true);
    delete t;
    delete(s);
    delete(s1);
}