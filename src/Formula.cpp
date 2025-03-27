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
    if (cell == this->formulaCell || cell == nullptr)
        return;

    // we need to find the cell in the list: we use a lambda function to define a pointer which will be eventually find by the get() method

    auto c = std::find_if(involvedCells.begin(), involvedCells.end(),
                          [cell](const std::shared_ptr<Cell>& ptr) {
                              return ptr.get() == cell;
                          });

    // at this moment, if the pointer IS NOT on the list, we can add it to the list, while creating the shared pointer first.

    if (c == involvedCells.end()) {
        std::shared_ptr<Cell> sharedCell(std::shared_ptr<Cell>(), cell);
        involvedCells.push_back(sharedCell);
        cell->subscribe(this);
    }
    update();
}