//
// Created by leo on 08/04/25.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/Cell.h"
#include "../src/Sum.h"
#include "MockObserver.h"
#include <memory>


using ::testing::AtLeast;

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

// Test that observers are properly notified when the cell data changes using a mock Class
TEST(CellTest, MockObserverSetData) {
    Cell cell;
    auto *observer = new ObserverMock();
    cell.subscribe(observer);
    EXPECT_CALL(*observer, update()).Times(1); // we are expecting a single call to the update() method
    cell.setData(0, 22.45); // this method calls for update()
    delete observer;
}

// Test for unsubscribing observers
TEST(CellTest, UnsubscribeMockObserver) {
    Cell cell;
    auto* observer = new ObserverMock();
    cell.subscribe(observer);
    EXPECT_CALL(*observer, update()).Times(1); // test for a single call
    cell.setData(0,2);
    cell.unsubscribe(observer);
    EXPECT_CALL(*observer, update()).Times(0); // now we are not expecting calls for update on the observer side, as there are not any observers in the list
    cell.setData(0, 1.21);
    delete observer;
}

// Test for multiple observers
TEST(CellTest, MultipleMockObservers) {
    Cell cell;

    // Create two mock observers and subscribe them to the cell's list of observers
    auto *observer1 = new ObserverMock();
    auto *observer2 = new ObserverMock();
    cell.subscribe(observer1);
    cell.subscribe(observer2);
    EXPECT_CALL(*observer1, update()).Times(1);
    EXPECT_CALL(*observer2, update()).Times(1);

    cell.setData(0, 66.0); // this call should trigger a call for each of the observers

    delete observer1;
    delete observer2;
}

// test for updating when resetting a cell
TEST(CellTest, ResetUpdate) {
    Cell cell(11.39);
    auto *observer = new ObserverMock();;
    cell.subscribe(observer);
    EXPECT_CALL(*observer, update()).Times(2);
    cell.resetCell(); // should call twice for the update() method, once for the “overloaded” setData() method and once again for the setBackground method which calls the setData method again but with a different role

    delete observer;
}