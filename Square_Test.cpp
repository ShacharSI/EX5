
#include "Square.h"
#include <gtest/gtest.h>

/**
 * square testing
 */
class Square_Test: public ::testing::Test{


protected:
    Square* s1;
    Square* s2;

    virtual void setUp(){
        this->s1 =new Square(1,2);
        this->s2 = new Square(Point(1,2));
    }
    virtual void TearDown(){
        cout<<"tearingDown";
        delete s1;
        delete s2;
    }

public:
    Square_Test() {
        this->setUp();
    }
};

/**
 * test the square's getters
 */
TEST_F(Square_Test,checkGetters){
    EXPECT_EQ(this->s1->getVisited(), false);
    EXPECT_EQ(this->s1->isVisitBottom(), false);
    EXPECT_EQ(this->s1->isVisitUp(), false);
    EXPECT_EQ(this->s1->isVisitLeft(), false);
    EXPECT_EQ(this->s1->isVisitRIght(), false);
    EXPECT_EQ(this->s1->getPoint().equals(Point(1,2)), true);
    EXPECT_EQ(this->s1->getBfsVal(),0);
    EXPECT_EQ(this->s1->isObstacleFlag(), false);
}

/**
 * checking the square setters
 */
TEST_F(Square_Test,checkSetter){
    this->s1->setBfsVal(3);
    EXPECT_EQ(this->s1->getBfsVal(),3);
    this->s1->setBfsFather(this->s2);
    EXPECT_EQ(this->s1->getBstFather(),s2);
    this->s1->setSon(3);
    EXPECT_EQ(3,this->s1->getSon());
    this->s1->setVisitB(true);
    EXPECT_EQ(true,this->s1->isVisitBottom());
    this->s1->setVisitL(true);
    EXPECT_EQ(true,this->s1->isVisitLeft());
    this->s1->setVisitR(true);
    EXPECT_EQ(true,this->s1->isVisitRIght());
    this->s1->setVisitU(true);
    EXPECT_EQ(true,this->s1->isVisitUp());

}

/**
 * checking the function that check's if to
 * update a neibghor's bfs val
 */
TEST_F(Square_Test,checkVal){
    this->s2->setBfsVal(23);
    this->s2->setBfsVal(23);
    this->s1->setBfsVal(2);
    ASSERT_EQ(this->s1->checkVal(s1,s2), true);
}

/**
 * checking that a list is created properly
 * in the create list function
 */
TEST_F(Square_Test,checkList){
    this->s1->setBfsFather(this->s2);
    this->s2->setBfsFather(NULL);
    std::list<Searchable*> l;
    EXPECT_EQ(0,l.size());
    l = this->s1->createList();;
    EXPECT_EQ(2,l.size());
    Point p = l.front()->getPoint();
    EXPECT_EQ(Point(1,2).equals(p),true);
}

/**
 * checking that the update neiboghr is working properly
 */
TEST_F(Square_Test,checkUpdate){
    queue<Square*> q;
    q.push(this->s2);
    this->s2->setBfsVal(100);
    EXPECT_EQ(this->s2->getBfsVal(),100);
    this->s1->setBfsVal(3);
    EXPECT_EQ(this->s1->getBfsVal(),3);
    this->s1->leftSon = this->s2;
    this->s1->updateNeiboghr(q);
    EXPECT_EQ(this->s2->getBfsVal(),4);
}