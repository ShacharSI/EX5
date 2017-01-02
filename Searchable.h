
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

    virtual list <Searchable*> createList()=0;
    virtual void setAll() =0;
    virtual void createRout()=0;
    virtual Point getPoint() = 0;
    virtual void setStartVal()=0;
    virtual void setBeforeBfs(std::list<Searchable*> l) = 0;

};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Searchable);
#endif //EX1TM_SERCHABLE_H