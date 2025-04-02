#pragma once
#include "Formula.h"

#ifndef SUM_H
#define SUM_H


class Sum :public Formula {
public:
    explicit Sum (Cell* cell) : Formula(cell) {}
    void calculate() override;
    [[nodiscard]] QColor getColor() const override;
};



#endif //SUM_H
