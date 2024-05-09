#include "Spreadsheet.h"

Spreadsheet::Spreadsheet(QWidget *parent): QTableWidget(parent) {}

Spreadsheet::Spreadsheet(int rows, int cols, QWidget *parent): QTableWidget(parent) {
    setRowCount(rows);
    setColumnCount(cols);
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j < cols; j++) {
            Cell *cell = new Cell("");
            this->setItem(i, j, cell);
        }
    }
}

void Spreadsheet::setColumnTitle(int colIndex, const QString &title) {
    setHorizontalHeaderItem(colIndex, new QTableWidgetItem(title, QTableWidgetItem::Type));
}

const int Spreadsheet::getRows() const {
    return this->rowCount();
}

const int Spreadsheet::getColumns() const {
    return this->columnCount();
}

void Spreadsheet::setRows(int r) {
    setRowCount(r);
}

void Spreadsheet::setCols(int c) {
    setColumnCount(c);
}

void Spreadsheet::setCellValue(Cell *c, double v) {
    c->setText(QString::number(v));
}

Cell Spreadsheet::getCell(int r, int c) {
}
