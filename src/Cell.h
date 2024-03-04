#ifndef QT_SPREADSHEET_CELL_H
#define QT_SPREADSHEET_CELL_H

#include <list>
#include <memory>

#include "Subject.h"
// #include "Formula.h"

class Cell: public Subject, public Observer{ // every cell is both a Subject and an Observer
public:


    ~Cell() override = default;

    void setValue(float v);
    double getValue() const;
    // from subject
    void notify() override ; // virtual is redundant
    void subscribe(Observer* o)override ;
    void unsubscribe(Observer* o)override ;


private:
    double value;
    bool hasValue;
    std::list<std::shared_ptr<Cell>> cellSelection; // list of shared pointers -> I want to be able to do a cell selection
    std::list<Observer*> observers;


};

#endif //QT_SPREADSHEET_CELL_H
