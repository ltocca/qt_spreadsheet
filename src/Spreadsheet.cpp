#include "Spreadsheet.h"

Spreadsheet::Spreadsheet(int rows, int columns, QWidget *parent): QTableWidget(rows, columns, parent){
    //setRowCount(10);
    //setColumnCount(10);
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            auto *cell = new Cell();
            this->setItem(row, column, cell);
        }
    }
    this->numberRC(rows, columns);
}

Cell* Spreadsheet::getSelectedCell() const {
    QModelIndex currentIndex = this->currentIndex();  // Get the currently selected index
    if (!currentIndex.isValid()) {
        return nullptr;  // No cell is selected
    }
    return dynamic_cast<Cell*>(this->item(currentIndex.row(), currentIndex.column()));
}

Cell * Spreadsheet::getCell(int row, int col) const {
    return dynamic_cast<Cell*>(this->item(row, col));
}

void Spreadsheet::numberRC(const int rows, const int cols) {
    QStringList rowHeaders;
    for (int i = 0; i < rows; ++i) {
        rowHeaders << QString::number(i);
    }
    QStringList columnHeaders;
    for (int i = 0; i < cols; ++i) {
        columnHeaders << QString::number(i);
    }
    this->setHorizontalHeaderLabels(columnHeaders);
    this->setVerticalHeaderLabels(rowHeaders);
}
