#include <gtest/gtest.h>
#include "LuxTaxiFactory.h"
class LuxTaxiFactory_Test: public ::testing:: Test{

protected:
    LuxTaxiFactory luxTaxFact;

    virtual void setUp() {
        luxTaxFact = LuxTaxiFactory(25);
    }

    virtual void TearDown(){
        cout<<"tearingDown";
    }

};

TEST_F(LuxTaxiFactory_Test,checkCreate) {
    int id = 8;
    Taxi* luxTaxi = this->luxTaxFact.createTaxi(id,Taxi::HONDA,Taxi::RED);
    ASSERT_EQ(luxTaxi->getCarId(),id);
    ASSERT_EQ(luxTaxi->getClr(),Taxi::RED);
    ASSERT_EQ(luxTaxi->getMnfctr(),Taxi::HONDA);
}