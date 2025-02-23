#include "Min.h"

void Min::calculate() {
    if (involvedCells.empty()) {
        this->formulaCell->setData(0, 0.0);  // Default value when no cells
        return;
    }

    double min = involvedCells.front()->getData();
    for (const auto& cell : involvedCells) {
        if (const double value = cell->getData(); value < min) {
            min = value;
        }
    }
    this->formulaCell->setData(0, min);
}