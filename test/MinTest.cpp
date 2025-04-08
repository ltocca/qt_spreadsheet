//
// Created by leo on 08/04/25.
//


#include "gtest/gtest.h"
#include "../src/Min.h"
#include <memory>


// Test basic Min functionality
TEST(MinTest, Basic) {\
    auto formulaCell = new Cell();
    auto min = new Min(formulaCell);
    for (int i = 0; i < 3; i++) {
        auto cell = new Cell(i+1);
        min->addCell(cell);
    }
    EXPECT_DOUBLE_EQ(1.0, formulaCell->getData());

    // Clean up
    delete min;
    delete formulaCell;
    // Note: We would need to cleanup the cells too, but we don't have a way to access them
}

// Test Min with negative values
TEST(MinTest, NegativeValues) {
    auto formulaCell = new Cell();
    auto min = new Min(formulaCell);

    auto cell1 = new Cell(10.0);
    auto cell2 = new Cell(-34.5);
    auto cell3 = new Cell(5.0);

    min->addCell(cell1);
    min->addCell(cell2);
    min->addCell(cell3);

    EXPECT_DOUBLE_EQ(-34.5, formulaCell->getData());

    // Clean up
    delete min;
    delete formulaCell;
    delete cell1;
    delete cell2;
    delete cell3;
}

// Test Min with no cells
TEST(MinTest, EmptyMin) {
    auto formulaCell = new Cell();
    auto min = new Min(formulaCell);

    // With no cells added, the min should be 0
    min->calculate();
    EXPECT_DOUBLE_EQ(0.0, formulaCell->getData());

    // Clean up
    delete min;
    delete formulaCell;
}

// Test the color
TEST(MinTest, MinColor) {
    auto formulaCell = new Cell();
    auto min = new Min(formulaCell);

    QColor color = min->getColor();
    EXPECT_EQ(251, color.red());
    EXPECT_EQ(99, color.green());
    EXPECT_EQ(99, color.blue());

    // Clean up
    delete min;
    delete formulaCell;
}