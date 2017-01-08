//
// Created by sha on 1/8/17.
//

#ifndef EX3_TM_BFSSTEP_H
#define EX3_TM_BFSSTEP_H


#include "Searchable.h"

class BfsStep {
private:
    Searchable* current;
    BfsStep* previous;
public:
    BfsStep();
    BfsStep(Searchable * current);
    void SetPrevious(BfsStep* previous);
};


#endif //EX3_TM_BFSSTEP_H
