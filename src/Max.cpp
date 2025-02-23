#include "Max.h"

void Max::calculate() {
    if (involvedCells.empty()) {
        this->formulaCell->setData(0, 0.0);  // Default value when no cells
        return;
    }
    
    double max = involvedCells.front()->getData();
    for (const auto& cell : involvedCells) {
        if (const double value = cell->getData(); value > max) {
            max = value;
        }
    }
    this->formulaCell->setData(0, max);
}