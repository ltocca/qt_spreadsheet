#pragma once
#include "Formula.h"

#ifndef MEAN_H
#define MEAN_H



class Mean : public Formula {
public:
  explicit Mean(Cell* cell) : Formula(cell) {}
  void calculate() override;
};



#endif //MEAN_H
