#pragma once
#include "Formula.h"

#ifndef MAX_H
#define MAX_H



class Max: public Formula {
public:
    explicit Max(Cell* opCell) : Formula(opCell){}
    void calculate() override;
};



#endif //MAX_H
