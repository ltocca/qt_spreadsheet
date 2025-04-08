//
// Created by leo on 08/04/25.
//

#include "gtest/gtest.h"
#include "../src/Mean.h"
#include <memory>


// Test basic Mean functionality
TEST(MeanTest, Basic) {
    auto formulaCell = new Cell();
    auto mean = new Mean(formulaCell);
    for (int i = 0; i < 3; i++) {
        auto cell = new Cell(i+1);
        mean->addCell(cell);
    }
    EXPECT_DOUBLE_EQ(2.0, formulaCell->getData());

    // Clean up
    delete mean;
    delete formulaCell;
    // Note: We would need to cleanup the cells too, but we don't have a way to access them
}

// Test Mean with negative values
TEST(MeanTest, NegativeValues) {
    auto formulaCell = new Cell();
    auto mean = new Mean(formulaCell);

    auto cell1 = new Cell(10.0);
    auto cell2 = new Cell(-24.0);
    auto cell3 = new Cell(5.0);

    mean->addCell(cell1);
    mean->addCell(cell2);
    mean->addCell(cell3);

    EXPECT_DOUBLE_EQ(-3.0, formulaCell->getData());

    // Clean up
    delete mean;
    delete formulaCell;
    delete cell1;
    delete cell2;
    delete cell3;
}

// Test Mean with no cells
TEST(MeanTest, EmptyMean) {
    auto formulaCell = new Cell();
    auto mean = new Mean(formulaCell);

    // With no cells added, the Mean should be 0
    mean->calculate();
    EXPECT_DOUBLE_EQ(0.0, formulaCell->getData());

    // Clean up
    delete mean;
    delete formulaCell;
}

// Test the color
TEST(MeanTest, MeanColor) {
    auto formulaCell = new Cell();
    auto mean = new Mean(formulaCell);

    QColor color = mean->getColor();
    EXPECT_EQ(253, color.red());
    EXPECT_EQ(253, color.green());
    EXPECT_EQ(91, color.blue());

    // Clean up
    delete mean;
    delete formulaCell;
}