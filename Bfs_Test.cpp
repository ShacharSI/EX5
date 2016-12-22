//
// Created by haim on 12/2/16.
//


#include <gtest/gtest.h>
#include "Logic.h"

/**
 * testing the bfs algo
 */
class Bfs_Test : public ::testing::Test {


protected:

    virtual void setUp() {


    }

    virtual void TearDown() {

    }

public:
    Bfs_Test() {
    }
};


/**
 * creating a map then gives 2 points on it
 * and checks that we got the correct routh
 */
TEST_F(Bfs_Test, checkBfs1) {
    vector<int> v;
    v.push_back(4);
    v.push_back(3);
    Logic logic(v);
    Point p(2, 1);
    Map map = logic.createNewMap("Square");
    Searchable *start = map.getStart();
    Searchable *des = map.findOnGrid(p);
    std::list<Searchable *> l;
    Bfs bfs;
    l = bfs.findRouth(start, des);
    ASSERT_EQ(l.size(), 4);
    ASSERT_EQ(l.front()->getPoint().equals((Point(0, 0))), true);
    l.pop_front();
    ASSERT_EQ(l.front()->getPoint().equals((Point(0, 1))), true);
    l.pop_front();
    ASSERT_EQ(l.front()->getPoint().equals((Point(1, 1))), true);
    l.pop_front();
    ASSERT_EQ(l.front()->getPoint().equals((Point(2, 1))), true);
    l.pop_front();

}

/**
 * creating a map then gives 2 points on it
 * and checks that we got the correct routh
 */
TEST_F(Bfs_Test, checkBfs2) {
    vector<int> v;
    v.push_back(3);
    v.push_back(4);
    Logic logic(v);
    Point p(1, 0);
    Map map = logic.createNewMap("Square");
    Searchable *start = map.getStart();
    Searchable *des = map.findOnGrid(p);
    std::list<Searchable *> l;
    Bfs bfs;
    l = bfs.findRouth(start, des);
    ASSERT_EQ(l.size(),2);
    ASSERT_EQ(l.front()->getPoint().equals((Point(0, 0))), true);
    l.pop_front();
    ASSERT_EQ(l.front()->getPoint().equals((Point(1, 0))), true);
    l.pop_front();
}

/**
 * checking that a routh from a point to himself
 * is in size 1-only the point himself
 */
TEST_F(Bfs_Test, checkPointToHimself) {
    vector<int> v;
    v.push_back(3);
    v.push_back(3);
    Logic logic(v);
    Point p(0, 0);
    Map map = logic.createNewMap("Square");
    Searchable *start = map.getStart();
    Searchable *des = map.findOnGrid(p);
    std::list<Searchable *> l;
    Bfs bfs;
    l = bfs.findRouth(start, des);
    ASSERT_EQ(l.size(), 1);
    ASSERT_EQ(l.front()->getPoint().equals((Point(0, 0))), true);

}