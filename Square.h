
#include "Point.h"
#include "Searchable.h"
#include <queue>

#ifndef EX1TM_SQUARE_H
#define EX1TM_SQUARE_H

/**
 * a class that "implempents" the searchable interface
 * and represents a point on map that can be searched.
 */
class Square : public Searchable {

public:

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Searchable>(*this);
        ar & point;

    }


    Square(Point p1);

    Square(int x, int y);

    Square();

    ~Square();

    int validate();

    Point getPoint();

    Searchable *getFather();

    bool getBfsVisited();

    bool setBfsVisited(bool b);

    void setBfsFather(Searchable *s);

    bool isObstacle();

    void setObstacle(bool b) ;


private:

    Point point;
    Square *bfsFather;
    bool setAllVisted;
    bool bfsVisited;
    bool obstacle;

};


#endif //EX1TM_SQUARE_H