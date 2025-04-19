//
// Created by leo on 19/04/25.
//



#include "gtest/gtest.h"
#include "../src/Max.h"
#include <memory>


// Test basic Max functionality
TEST(MaxTest, Basic) {\
    auto formulaCell = new Cell();
    auto max = new Max(formulaCell);
    for (int i = 0; i < 3; i++) {
        auto cell = new Cell(i+1);
        max->addCell(cell);
    }
    EXPECT_DOUBLE_EQ(3.0, formulaCell->getData());

    // Clean up
    delete max;
    delete formulaCell;
    // Note: We would need to cleanup the cells too, but we don't have a way to access them
}

// Test Max with negative values
TEST(MaxTest, NegativeValues) {
    auto formulaCell = new Cell();
    auto max = new Max(formulaCell);

    auto cell1 = new Cell(10.0);
    auto cell2 = new Cell(-34.5);
    auto cell3 = new Cell(5.0);

    max->addCell(cell1);
    max->addCell(cell2);
    max->addCell(cell3);

    EXPECT_DOUBLE_EQ(10, formulaCell->getData());

    // Clean up
    delete max;
    delete formulaCell;
    delete cell1;
    delete cell2;
    delete cell3;
}

// Test Max with no cells
TEST(MaxTest, EmptyMax) {
    auto formulaCell = new Cell();
    auto max = new Max(formulaCell);

    // With no cells added, the max should be 0
    max->calculate();
    EXPECT_DOUBLE_EQ(0.0, formulaCell->getData());

    // Clean up
    delete max;
    delete formulaCell;
}

// Test the color
TEST(MaxTest, MaxColor) {
    auto formulaCell = new Cell();
    auto max = new Max(formulaCell);

    QColor color = max->getColor();
    EXPECT_EQ(40, color.red());
    EXPECT_EQ(159, color.green());
    EXPECT_EQ(40, color.blue());

    // Clean up
    delete max;
    delete formulaCell;
}