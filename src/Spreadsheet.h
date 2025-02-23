#pragma once
#include "Cell.h"
#include "QTableWidget"

#ifndef SPREADSHEET_H
#define SPREADSHEET_H



class Spreadsheet final : public QTableWidget {
    Q_OBJECT
public:
    explicit Spreadsheet(int rows = 10, int columns = 10, QWidget *parent = nullptr);
    [[nodiscard]] Cell* getSelectedCell() const;
    [[nodiscard]] Cell* getCell(int row, int col) const;

    void numberRC(int rows, int cols); // edit the number of columns and rows labels

};



#endif //SPREADSHEET_H
