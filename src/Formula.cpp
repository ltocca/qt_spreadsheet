#include "Formula.h"

Formula::~Formula() {
    for (const auto& cell : involvedCells) {
        cell->unsubscribe(this);
    }
}

void Formula::update() {
    calculate();
}


void Formula::addCell(Cell* cell) {
    // Don't add null cells or the formula's own cell
    if (cell == nullptr || cell == this->formulaCell)
        return;

    // to use this bool variable we need to use C++20!!
    // we need to find the cell in the list: we use a bool function to define a pointer which will be eventually find by the get() method
    // any_of check if unary predicate is equal to a shared pointer
    // const bool cellExists = std::ranges::any_of(involvedCells,[cell](const auto& ptr) {return ptr.get() == cell;});

    // Only add cell if it's not already in the list
    if (!cellInvolved(*cell)) {
        // Create a non-owning shared_ptr (observer pointer)
        const std::shared_ptr<Cell> cellPtr(std::shared_ptr<Cell>(), cell);
        involvedCells.push_back(cellPtr);
        cell->subscribe(this);
    }

    update();
}

bool Formula::cellInvolved(const Cell &cell) const {
    bool involved = false;
    for (auto& ic : involvedCells) {
        if (ic.get() == &cell) {
            involved = true;
            break;
        }
    }
    return involved;
}
