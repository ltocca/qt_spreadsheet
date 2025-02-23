#include "Sum.h"

void Sum::calculate() {
    if (involvedCells.empty()) {
        this->formulaCell->setData(0, 0.0);  // Default value when no cells
        return;
    }

    double sum = 0.0;
    for (const auto& cell : involvedCells) {
        sum += cell->getData();
    }
    this->formulaCell->setData(0, sum);
}
