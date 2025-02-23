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
    
    auto sharedCell = std::shared_ptr<Cell>(cell);  // Create shared_ptr from raw pointer
    involvedCells.push_back(sharedCell);
    cell->subscribe(this);
    calculate();
}

void Formula::removeCell(Cell* cell) {
    if (cell == this->formulaCell || cell == nullptr)
        return;
    
    involvedCells.remove_if([cell](const std::shared_ptr<Cell>& ptr) {
        return ptr.get() == cell;
    });
    cell->unsubscribe(this);
    calculate();
}