#pragma once
#include "Formula.h"

#ifndef MIN_H
#define MIN_H



class Min : public Formula {
public:
    explicit Min(Cell* cell) : Formula(cell) {}
    void calculate() override;
    [[nodiscard]] QColor getColor() const override;
};



#endif //MIN_H
