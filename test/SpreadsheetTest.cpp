//
// Created by leo on 09/04/25.
//
#include "gtest/gtest.h"
#include "../src/Spreadsheet.h"
#include "../src/UserInterface.h"
#include "Cell.h"
#include <QApplication>

// Required for Qt GUI testing
// Using the Google Test Environment class to initialize QApplication
class QtTestEnvironment : public ::testing::Environment {
public:
    QtTestEnvironment() {
        if (QApplication::instance() == nullptr) {
            static int argc = 1;
            static char* argv[] = {(char*)"Dummy"};
            static QApplication app(argc, argv);
            // QApplication is now initialized and accessible via QApplication::instance()
        }
    }

    ~QtTestEnvironment() override = default;
};
// Add the environment to be set up before tests run
::testing::Environment* const qtEnvironment =
    ::testing::AddGlobalTestEnvironment(new QtTestEnvironment);

class SpreadsheetTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a 5x5 spreadsheet for testing
        spreadsheet = new Spreadsheet(5, 5);
    }

    void TearDown() override {
        delete spreadsheet;
    }

    Spreadsheet* spreadsheet;
};

TEST_F(SpreadsheetTest, CheckConstructorSize) {
    EXPECT_EQ(5, spreadsheet->rowCount());
    EXPECT_EQ(5, spreadsheet->columnCount());
}

TEST_F(SpreadsheetTest, CheckCellInit) {
    for (int row = 0; row < spreadsheet->rowCount(); row++) {
        for (int col = 0; col < spreadsheet->columnCount(); col++) {
            Cell* cell = spreadsheet->getCell(row, col);
            EXPECT_NE(nullptr, cell);
            EXPECT_EQ(0.0, cell->getData());
            EXPECT_FALSE(cell->hasFormula());
        }
    }
}

TEST_F(SpreadsheetTest, NumberRCCheckHeaders) {
    // Headers should be numbers as strings
    for (int i = 0; i < spreadsheet->rowCount(); i++) {
        EXPECT_EQ(QString::number(i), spreadsheet->verticalHeaderItem(i)->text());
    }
    for (int i = 0; i < spreadsheet->columnCount(); i++) {
        EXPECT_EQ(QString::number(i), spreadsheet->horizontalHeaderItem(i)->text());
    }
}

TEST_F(SpreadsheetTest, GetCellReturnsCorrectCell) {
    // Set data in a specific cell
    Cell* cell = spreadsheet->getCell(2, 3);
    // Instead of using setData, we'll set the text to emulate a user inserting data from the gui
    cell->setText(QString::number(42.0));

    // Get the same cell again and verify
    Cell* retrievedCell = spreadsheet->getCell(2, 3);
    EXPECT_EQ(42.0, retrievedCell->getData());
    EXPECT_EQ(cell, retrievedCell);
}

TEST_F(SpreadsheetTest, GetCellNoSelection) {
    // By default, no cell is selected
    EXPECT_EQ(nullptr, spreadsheet->getSelectedCell());
}

TEST_F(SpreadsheetTest, GetSelectedCellCorrect) {
    // Emulate a user cell selection
    spreadsheet->setCurrentCell(1, 2);

    // Verify the selected cell is correctly returned
    Cell* selectedCell = spreadsheet->getSelectedCell();
    EXPECT_NE(nullptr, selectedCell);
    EXPECT_EQ(spreadsheet->getCell(1, 2), selectedCell);
}