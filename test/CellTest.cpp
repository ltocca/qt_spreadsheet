//
// Created by leo on 08/04/25.
//
#include "gtest/gtest.h"
#include "../src/Cell.h"
#include "../src/Sum.h"
#include <memory>

// Test the Cell constructor and getData functionality
TEST(CellTest, ConstructorAndGetData) {
    // Test default constructor
    Cell defaultCell;
    EXPECT_DOUBLE_EQ(0.0, defaultCell.getData());

    // Test constructor with value
    Cell valueCell(42.5);
    EXPECT_DOUBLE_EQ(42.5, valueCell.getData());
}

// Test the setData method
TEST(CellTest, SetData) {
    Cell cell;
    cell.setData(0, 123.45);
    EXPECT_DOUBLE_EQ(123.45, cell.getData());

    // Test with different value
    cell.setData(0, -67.89);
    EXPECT_DOUBLE_EQ(-67.89, cell.getData());
}

// Test the hasFormula method
TEST(CellTest, HasFormula) {
    auto cell = new Cell();
    // Initially, a cell should have no formula
    EXPECT_FALSE(cell->hasFormula());

    auto f = new Sum(cell);
    cell->setFormula(f);
    EXPECT_TRUE(cell->hasFormula());

    delete f;
    delete cell;
}

// Test resetCell functionality
TEST(CellTest, ResetCell) {
    Cell cell(123.45);
    cell.resetCell();
    EXPECT_DOUBLE_EQ(0.0, cell.getData());
    // Color and observers would also be reset, but that's harder to test directly
}