//
// Created by sha on 1/8/17.
//

#include "BfsStep.h"

BfsStep::BfsStep() {

}

BfsStep::BfsStep(Searchable *current) {
    this->current = current;
}

void BfsStep::SetPrevious(BfsStep *previous) {
    this->previous = previous;
}
