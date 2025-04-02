#include "Mean.h"

void Mean::calculate() {
    if (involvedCells.empty()) {
        this->formulaCell->setData(0, 0.0);  // Default value when no cells
        return;
    }

    double sum = 0.0;
    for (const auto& cell : involvedCells) {
        sum += cell->getData();
    }
    double avg = sum / static_cast<double>(involvedCells.size());
    this->formulaCell->setData(0, avg);
}

QColor Mean::getColor() const {
    return {253, 253, 91};
}