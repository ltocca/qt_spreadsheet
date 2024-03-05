#ifndef QT_SPREADSHEET_CELL_H
#define QT_SPREADSHEET_CELL_H

#include <list>
#include <memory>
#include <QtWidgets/QTableWidgetItem>

#include "Subject.h"
// #include "Formula.h"

class Cell : public Subject, public Observer, public QTableWidgetItem {
    // every cell is both a Subject and an Observer
public:

    // TODO: find how the constructor must be
    ~Cell() override = default;

    void setValue(double v);
    const double getValue() const;

    void setCustomValue(bool cv);
    const bool checkCustomValue() const;

    // from subject and observer

    void notify() override; // virtual is redundant
    void update() override;
    void subscribe(Observer *o) override;
    void unsubscribe(Observer *o) override;

private:
    // TODO find QT variables
    double value;
    bool customValue; // variable to check if the cell has been modified since its creation
    std::list<std::shared_ptr<Cell> > cellSelection; // list of shared pointers to involved cells-> I want to be able to do a cell selection
    std::list<Observer *> observers;
};

#endif //QT_SPREADSHEET_CELL_H
