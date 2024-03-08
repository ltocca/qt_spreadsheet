#ifndef QT_SPREADSHEET_CELL_H
#define QT_SPREADSHEET_CELL_H

#include <list>
#include <memory>
#include <QtWidgets/QTableWidgetItem>

#include "Subject.h"
#include "Formula.h"
#include "Max.h"
#include "Mean.h"
#include "Min.h"
#include "Sum.h"

class Cell : public QTableWidgetItem, public Subject, public Observer {
    // every cell is both a Subject and an Observer
public:
    // TODO: find how the constructor must be
    //Cell(double v);
    ~Cell() override = default;

    void setValue(double v);
    double getValue() const;

    void setData(int role, const QVariant &value) override;
    float getData();

    void setCustomValue(bool cv);
    bool checkCustomValue() const;

    void selectCells(std::list<std::shared_ptr<Cell>> cs);
    void addCell(Cell& c);
    std::list<double> extractValues(std::list<std::shared_ptr<Cell>>& cs);

    void Cell::setFormula(int fType, std::list<std::shared_ptr<Cell>>& involvedCells, const std::string& f);
    const std::shared_ptr<Formula>& Cell::getFormula() const ;
    void Cell::removeFormula();

    // from subject and observer

    void notify() override; // virtual is redundant
    void update() override;
    void subscribe(Observer *o) override;
    void unsubscribe(Observer *o) override;

private:
    // TODO find QT variables
    // TODO Qstring for saving formula
    QVariant value;
    // QString formula = nullptr;
    // double value;
    bool customValue = false; // variable to check if the cell has been modified since its creation
    // bool isText; maybe to check if the formula is correct or is only text
    std::shared_ptr<Formula> formula;
    std::list<std::shared_ptr<Cell>> cellSelection; // list of shared pointers to involved cells-> I want to be able to do a cell selection
    std::list<Observer *> observers;
};

#endif //QT_SPREADSHEET_CELL_H
