//
// Created by leo on 09/04/25.
//
#include "gtest/gtest.h"
#include "UserInterface.h"
#include "Spreadsheet.h"
#include "Sum.h"
#include "Max.h"
#include "Min.h"
#include "Mean.h"
#include <QApplication>
#include <QMessageBox>
#include <QPushButton>
#include <QToolBar>
#include <QInputDialog>

class UserInterfaceTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Disable QMessageBox for tests
        qputenv("QT_NO_MESSAGEBOX", "1");
        ui = new UserInterface(nullptr);
    }

    void TearDown() override {
        delete ui;
    }

    UserInterface* ui;
};

TEST_F(UserInterfaceTest, SpreadsheetIsCreated) {
    // Access the spreadsheet through its parent widget
    QWidget* centralWidget = ui->centralWidget();
    ASSERT_NE(nullptr, centralWidget);

    // Find the spreadsheet using findChild
    Spreadsheet* spreadsheet = centralWidget->findChild<Spreadsheet*>();
    EXPECT_NE(nullptr, spreadsheet);
}

TEST_F(UserInterfaceTest, ToolbarButtonsExist) {
    // Find buttons by searching through the toolbar
    auto* toolbar = ui->findChild<QToolBar*>();
    ASSERT_NE(nullptr, toolbar);

    QList<QPushButton*> buttons = toolbar->findChildren<QPushButton*>();
    EXPECT_GE(buttons.size(), 5); // We expect at least 5 buttons

    // Check if buttons with expected text exist
    bool foundSum = false;
    bool foundMax = false;
    bool foundMin = false;
    bool foundMean = false;
    bool foundReset = false;

    for (QPushButton* button : buttons) {
        if (button->text() == "Sum") foundSum = true;
        else if (button->text() == "Maximum") foundMax = true;
        else if (button->text() == "Minimum") foundMin = true;
        else if (button->text() == "Mean") foundMean = true;
        else if (button->text() == "Reset") foundReset = true;
    }

    EXPECT_TRUE(foundSum);
    EXPECT_TRUE(foundMax);
    EXPECT_TRUE(foundMin);
    EXPECT_TRUE(foundMean);
    EXPECT_TRUE(foundReset);
}

// Test window title and size
TEST_F(UserInterfaceTest, WindowProperties) {
    std::string x = ui->windowTitle().toStdString();
    std::cout<<x;
    EXPECT_FALSE(ui->windowTitle().isEmpty());
    EXPECT_GT(ui->width(), 0);
    EXPECT_GT(ui->height(), 0);
}

// Additional test that simulates user interaction with the UI

TEST_F(UserInterfaceTest, SpreadsheetInteraction) {
    // Find the spreadsheet
    auto* spreadsheet = ui->findChild<Spreadsheet*>();
    ASSERT_NE(nullptr, spreadsheet);

    // Check if we can interact with the spreadsheet
    // We'll just verify we can set and get cell values
    if (spreadsheet->rowCount() > 0 && spreadsheet->columnCount() > 0) {
        Cell* cell = spreadsheet->getCell(0, 0);
        ASSERT_NE(nullptr, cell);

        // Set text and check if it is saved in the cell
        cell->setText("123");
        EXPECT_EQ(123, cell->getData());
    }
}


// TODO: Find a way to implement