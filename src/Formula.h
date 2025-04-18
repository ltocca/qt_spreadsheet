//
// Created by leo on 12/02/25.
//

#pragma once
#include "QColor"
#include "Observer.h"
#include "Cell.h"
#include "list"
#include "memory"

#ifndef FORMULA_H
#define FORMULA_H



class Formula : public Observer{
public:
    explicit Formula(Cell* formulaCell): formulaCell(formulaCell){}
    ~Formula() override;

    void update() override;
    //void attach() override;
    //void detach() override;

    void addCell (Cell* cell);
    bool cellInvolved(const Cell& cell) const;
    static bool hasCircularReference(const Cell* fCell, const std::list<Cell*> &list) ;

    virtual void calculate() = 0;
    virtual QColor getColor() const = 0;

protected:
    Cell* formulaCell;
    std::list<std::shared_ptr<Cell>> involvedCells;
};



#endif //FORMULA_H
