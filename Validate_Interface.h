//
// Created by haim on 12/1/16.
//

#ifndef TM_VALIDATE_INTERFACE_H
#define TM_VALIDATE_INTERFACE_H


#include <boost/serialization/access.hpp>

/**
 * an interface that who ever is implempenting him checks
 * that the class worked properly
 */
class Vallidate_Interface{

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
    }

public:
    virtual  void validate() = 0;
};

#endif //TM_VALIDATE_INTERFACE_H