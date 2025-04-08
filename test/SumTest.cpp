//
// Created by leo on 07/04/25.
//

#include "gtest/gtest.h"
#include "../src/Sum.h"
#include <memory>


// Test basic sum functionality
TEST(SumTest, BasicSum) {
    auto formulaCell = new Cell();
    auto sum = new Sum(formulaCell);
    for (int i = 0; i < 3; i++) {
        auto cell = new Cell(i+1);
        sum->addCell(cell);
    }
    EXPECT_DOUBLE_EQ(6.0, formulaCell->getData());

    // Clean up
    delete sum;
    delete formulaCell;
    // Note: We would need to cleanup the cells too, but we don't have a way to access them
}

// Test sum with negative values
TEST(SumTest, NegativeValues) {
    auto formulaCell = new Cell();
    auto sum = new Sum(formulaCell);

    auto cell1 = new Cell(10.0);
    auto cell2 = new Cell(-20.0);
    auto cell3 = new Cell(5.0);

    sum->addCell(cell1);
    sum->addCell(cell2);
    sum->addCell(cell3);

    EXPECT_DOUBLE_EQ(-5.0, formulaCell->getData());

    // Clean up
    delete sum;
    delete formulaCell;
    delete cell1;
    delete cell2;
    delete cell3;
}

// Test sum with no cells
TEST(SumTest, EmptySum) {
    auto formulaCell = new Cell();
    auto sum = new Sum(formulaCell);

    // With no cells added, the sum should be 0
    sum->calculate();
    EXPECT_DOUBLE_EQ(0.0, formulaCell->getData());

    // Clean up
    delete sum;
    delete formulaCell;
}

// Test the color
TEST(SumTest, SumColor) {
    auto formulaCell = new Cell();
    auto sum = new Sum(formulaCell);

    QColor color = sum->getColor();
    EXPECT_EQ(124, color.red());
    EXPECT_EQ(124, color.green());
    EXPECT_EQ(252, color.blue());

    // Clean up
    delete sum;
    delete formulaCell;
}