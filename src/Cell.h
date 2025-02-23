#pragma once
#include "QTableWidget"
#include "Subject.h"

#ifndef CELL_H
#define CELL_H



class Cell :public Subject, public QTableWidgetItem {
public:
    Cell();
    explicit Cell(double v);
    ~Cell() override = default;

    [[nodiscard]] double getData() const;
    void setData(int role, const QVariant &data) override;

    void notify() override;
    void subscribe(Observer *o) override;
    void unsubscribe(Observer *o) override;


private:
    std::list<Observer*> observers;
};



#endif //CELL_H
