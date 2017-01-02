

#include <iosfwd>
#include <iostream>
#include <boost/serialization/base_object.hpp>
#include "Validate_Interface.h"

using namespace std;
#ifndef EX1TM_POINT_H
#define EX1TM_POINT_H

/**
 * a cllas that represent a point on map
 */
class Point: public Vallidate_Interface{

private:
    int x;
    int y;
public:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Vallidate_Interface>(*this);
        ar & x;
        ar & y;
    }
    Point(int x,int y);
    void validate();
    Point();
    ~Point();
    int getX();
    int getY();

    bool equals(Point p) const;

    friend ostream &operator << (ostream &output, Point &p){
        output << "("<<p.x<<","<<p.y<< ")"<< endl;
        return output;
    }


    friend istream &operator >> (istream &input, Point &p){
        input >> p.x>>p.y;
        return input;

    }

};


#endif //EX1TM_POINT_H