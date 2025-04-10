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
#include <QInputDialog>// Add this to your UITest.cpp file
#include <QTimer>
#include <QTest>

class UserInterfaceTest : public ::testing::Test {
protected:
    // Helper function to simulate text insertion into QInputDialog
    static void simulateInputDialog(const QString& inputText, bool accept = true) {
        // Use QTimer to interact with dialog after it appears
        QTimer::singleShot(100, [inputText, accept]() { // This static function calls a slot after a given time interval.
            // Extract the input dialog from the programs' widget list
            QWidgetList widgets = QApplication::topLevelWidgets();
            QInputDialog* dialog = nullptr;
            for (QWidget* widget : widgets) {
                dialog = qobject_cast<QInputDialog*>(widget);
                if (dialog)
                    break;
            }

            if (dialog) {
                dialog->setTextValue(inputText); // Set the text in the input field
                if (accept)
                    dialog->accept();
                else
                    dialog->reject();
            }
        });
    }

    // Helper function to check for error message boxes
    static bool checkForErrorMessageBox(const QString& expectedText = QString()) {
        QTest::qWait(200); // Wait for message box to appear

        // Find message boxes
        QWidgetList widgets = QApplication::topLevelWidgets();
        for (QWidget* widget : widgets) {
            if (auto* msgBox = qobject_cast<QMessageBox*>(widget)) {
                // If checking for specific text
                if (!expectedText.isEmpty() && msgBox->text().contains(expectedText)) {
                    // Close the message box to continue
                    QTest::keyClick(msgBox, Qt::Key_Enter);
                    return true;
                }
                if (expectedText.isEmpty()) {
                    // Close any message box found
                    QTest::keyClick(msgBox, Qt::Key_Enter);
                    return false;
                }
            }
        }
        return false;
    }

    void SetUp() override {
        // Disable QMessageBox for tests
        //qputenv("QT_NO_MESSAGEBOX", "1");
        simulateInputDialog("5,5", true);
        ui = new UserInterface(nullptr);
    }

    void TearDown() override {
        delete ui;
    }

    UserInterface* ui;
};

/***************
Begin Tests
***************/

TEST_F(UserInterfaceTest, SpreadsheetIsCreated) {
    // Access the spreadsheet through its parent widget
    QWidget* centralWidget = ui->centralWidget();
    ASSERT_NE(nullptr, centralWidget);

    // Find the spreadsheet using findChild
    auto* spreadsheet = centralWidget->findChild<Spreadsheet*>();
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
TEST_F(UserInterfaceTest, CreateSpreadsheetEmptyInput) {
    // Delete existing UI
    delete ui;

    // Setup a sequence where we first provide an empty input
    QTimer::singleShot(100, [this]() {
        // First dialog - enter empty text
        simulateInputDialog("", true);

        // After error message appears, handle it
        QTimer::singleShot(200, [this]() {
            checkForErrorMessageBox("Nothing was inserted");

            // Second dialog - enter valid dimensions
            QTimer::singleShot(200, [this]() {
                simulateInputDialog("3,3", true);
            });
        });
    });

    ui = new UserInterface(nullptr);

    // Wait for all async operations
    QTest::qWait(800);

    // Verify spreadsheet was eventually created
    auto* spreadsheet = ui->findChild<Spreadsheet*>();
    ASSERT_NE(nullptr, spreadsheet);
    EXPECT_EQ(3, spreadsheet->rowCount());
    EXPECT_EQ(3, spreadsheet->columnCount());
}

TEST_F(UserInterfaceTest, CreateSpreadsheetValidDimensions) {
    delete ui;
    simulateInputDialog("5,5");
    ui = new UserInterface(nullptr);
    auto* spreadsheet = ui->findChild<Spreadsheet*>();
    ASSERT_NE(nullptr, spreadsheet);
    EXPECT_EQ(5, spreadsheet->rowCount());
    EXPECT_EQ(5, spreadsheet->columnCount());
}

TEST_F(UserInterfaceTest, CreateSpreadsheetInvalidDimensions) {
    delete ui;
    QTimer::singleShot(100, [this]() {
        simulateInputDialog("15,15", true);

        // After error message appears, handle it
        QTimer::singleShot(200, [this]() {
            EXPECT_TRUE(checkForErrorMessageBox("maximum of 10 rows"));

            // try entering valid dimensions
            QTimer::singleShot(200, [this]() {
                simulateInputDialog("8,8", true);
            });
        });
    });
    ui = new UserInterface(nullptr);

    // Wait for all async operations to complete
    QTest::qWait(800);

    // Verify valid spreadsheet was eventually created
    auto* spreadsheet = ui->findChild<Spreadsheet*>();
    ASSERT_NE(nullptr, spreadsheet);
    EXPECT_EQ(8, spreadsheet->rowCount());
    EXPECT_EQ(8, spreadsheet->columnCount());
}

TEST_F(UserInterfaceTest, CreateSpreadsheetNegativeDimensions) {
    delete ui;

    QTimer::singleShot(100, [this]() {
        simulateInputDialog("-5,3", true);

        // Handle error message
        QTimer::singleShot(200, [this]() {
            EXPECT_TRUE(checkForErrorMessageBox("greater than 0"));

            QTimer::singleShot(200, [this]() {
                simulateInputDialog("4,4", true);
            });
        });
    });

    ui = new UserInterface(nullptr);

    // Wait for all async operations
    QTest::qWait(800);

    auto* spreadsheet = ui->findChild<Spreadsheet*>();
    ASSERT_NE(nullptr, spreadsheet);
    EXPECT_EQ(4, spreadsheet->rowCount());
    EXPECT_EQ(4, spreadsheet->columnCount());
}

// Tests for Formula Input Dialog

TEST_F(UserInterfaceTest, ValidFormula) {
    ui->findChild<Spreadsheet*>()->setCurrentCell(2, 2); // Select a cell

    QTimer::singleShot(100, [this]() {
        simulateInputDialog("00,01", true);
    });

    // Trigger the formula button click
    // Find the Sum button and click it
    auto* sumButton = ui->findChild<QPushButton*>("Sum");
    if (!sumButton) {
        // Try finding by text if name isn't set
        QList<QPushButton*> buttons = ui->findChildren<QPushButton*>();
        for (auto* button : buttons) {
            if (button->text() == "Sum") {
                sumButton = button;
                break;
            }
        }
    }

    ASSERT_NE(nullptr, sumButton);
    QTest::mouseClick(sumButton, Qt::LeftButton);

    // Wait for dialog processing
    QTest::qWait(300);

    // Verify the formula was created and set
    const auto* spreadsheet = ui->findChild<Spreadsheet*>();
    Cell* selectedCell = spreadsheet->getSelectedCell();
    ASSERT_NE(nullptr, selectedCell);
    EXPECT_TRUE(selectedCell->hasFormula());
}

TEST_F(UserInterfaceTest, FormulaInvalidCoordinates) {
    ui->findChild<Spreadsheet*>()->setCurrentCell(1, 1); // Select a cell

    QTimer::singleShot(100, [this]() {
        // First attempt with invalid coordinates
        simulateInputDialog("99,12", true);

        // Handle error message
        QTimer::singleShot(200, [this]() {
            EXPECT_TRUE(checkForErrorMessageBox("out of range"));

            // Second attempt with valid coordinates
            QTimer::singleShot(200, [this]() {
                simulateInputDialog("00,01", true);
            });
        });
    });

    // Find and click the Mean button
    QPushButton* meanButton = nullptr;
    QList<QPushButton*> buttons = ui->findChildren<QPushButton*>();
    for (auto* button : buttons) {
        if (button->text() == "Mean") {
            meanButton = button;
            break;
        }
    }

    ASSERT_NE(nullptr, meanButton);
    QTest::mouseClick(meanButton, Qt::LeftButton);

    // Wait for all operations
    QTest::qWait(800);

    // Verify formula was created
    auto* spreadsheet = ui->findChild<Spreadsheet*>();
    Cell* selectedCell = spreadsheet->getSelectedCell();
    ASSERT_NE(nullptr, selectedCell);
    EXPECT_TRUE(selectedCell->hasFormula());
}

TEST_F(UserInterfaceTest, FormulaCircularReference) {
    // Create necessary objects
    auto* spreadsheet = ui->findChild<Spreadsheet*>();
    spreadsheet->setCurrentCell(1, 1); // Select a cell

    QTimer::singleShot(100, [this]() {
        // Attempt to create a circular reference by including the current cell
        simulateInputDialog("11,22", true);

        // Handle error message
        QTimer::singleShot(200, [this]() {
            EXPECT_TRUE(checkForErrorMessageBox("circular reference"));

            // Then try with valid non-circular reference
            QTimer::singleShot(200, [this]() {
                simulateInputDialog("00:01", true);
            });
        });
    });

    // Find and click the Max button
    QPushButton* maxButton = nullptr;
    QList<QPushButton*> buttons = ui->findChildren<QPushButton*>();
    for (auto* button : buttons) {
        if (button->text() == "Maximum") {
            maxButton = button;
            break;
        }
    }

    ASSERT_NE(nullptr, maxButton);
    QTest::mouseClick(maxButton, Qt::LeftButton);

    // Wait for all operations
    QTest::qWait(800);

    // Verify formula was created with the valid input
    Cell* selectedCell = spreadsheet->getSelectedCell();
    ASSERT_NE(nullptr, selectedCell);
    EXPECT_TRUE(selectedCell->hasFormula());
}

TEST_F(UserInterfaceTest, FormulaRangeCoordinates) {
    // Create necessary objects
    auto* spreadsheet = ui->findChild<Spreadsheet*>();
    spreadsheet->setCurrentCell(2, 2); // Select a cell

    // Schedule dialog interaction
    QTimer::singleShot(100, [this]() {
        simulateInputDialog("00:11", true);
    });

    // Find and click the Min button
    QPushButton* minButton = nullptr;
    QList<QPushButton*> buttons = ui->findChildren<QPushButton*>();
    for (auto* button : buttons) {
        if (button->text() == "Minimum") {
            minButton = button;
            break;
        }
    }

    ASSERT_NE(nullptr, minButton);
    QTest::mouseClick(minButton, Qt::LeftButton);

    // Wait for operations
    QTest::qWait(300);

    // Verify formula was created
    Cell* selectedCell = spreadsheet->getSelectedCell();
    ASSERT_NE(nullptr, selectedCell);
    EXPECT_TRUE(selectedCell->hasFormula());
}

TEST_F(UserInterfaceTest, FormulaInvalidRange) {
    // Create necessary objects
    auto* spreadsheet = ui->findChild<Spreadsheet*>();
    spreadsheet->setCurrentCell(0, 0); // Select a cell

    // Schedule a sequence of interactions
    QTimer::singleShot(100, [this]() {
        // First attempt with invalid range (end before start)
        simulateInputDialog("33:11", true);

        // Handle error message
        QTimer::singleShot(200, [this]() {
            ASSERT_TRUE(checkForErrorMessageBox("wrong interval"));

            // Second attempt with valid range
            QTimer::singleShot(200, [this]() {
                simulateInputDialog("01:22", true);
            });
        });
    });

    /*// Find and click the Sum button
    QPushButton* sumButton = nullptr;
    QList<QPushButton*> buttons = ui->findChildren<QPushButton*>();
    for (auto* button : buttons) {
        if (button->text() == "Sum") {
            sumButton = button;
            break;
        }
    }

    ASSERT_NE(nullptr, sumButton);
    QTest::mouseClick(sumButton, Qt::LeftButton);

    // Wait for all operations
    QTest::qWait(800);

    // Verify formula was created with the valid input
    Cell* selectedCell = spreadsheet->getSelectedCell();
    ASSERT_NE(nullptr, selectedCell);
    EXPECT_TRUE(selectedCell->hasFormula());*/
}