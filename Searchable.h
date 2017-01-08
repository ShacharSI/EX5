
#ifndef EX1TM_SERCHABLE_H
#define EX1TM_SERCHABLE_H

#include <list>
#include "Point.h"

/**
 * a interface that represent a point on the
 * map,an object that can be search
 */
class Searchable {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {

    }

public:
    virtual Searchable *getFather() =0;

    virtual bool getBfsVisited()=0;

    virtual bool setBfsVisited(bool b)=0;

    virtual void setBfsFather(Searchable *s)=0;

    virtual bool isObstacle() = 0;

    virtual void setObstacle(bool b) = 0;

    virtual Point getPoint() = 0;

};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Searchable)
#endif //EX1TM_SERCHABLE_H