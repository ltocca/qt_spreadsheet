#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QtWidgets/QTableWidget>
#include "Cell.h"

class Spreadsheet: public QTableWidget{
public:
    explicit Spreadsheet(QWidget* parent = nullptr);
    Spreadsheet(int rows, int cols, QWidget* parent = nullptr);
    void setColumnTitle(int colIndex, const QString& title);

    const int getRows() const;
    const int getColumns() const;

    void setRows(int r);
    void setCols (int c);

    void setCellValue(Cell* c, double v);
    Cell getCell(int r, int c);

    // TODO: write methods to parse and calculate formulas


private:
    static const char CHAR_TO_NUMBER = '0';
    static const char EMPTY_SPACE = ' ';
    static const char COMMA = ',';
};



#endif //SPREADSHEET_H
