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


private:
};



#endif //SPREADSHEET_H
