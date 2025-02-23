#include "Cell.h"


Cell::Cell() {
    QTableWidgetItem::setData(0,0.00);
}

Cell::Cell(const double v) {
    QTableWidgetItem::setData(0, v);
}

double Cell::getData() const {
    return QTableWidgetItem::data(0).toDouble();
}

void Cell::setData(const int role, const QVariant &data) {
    QTableWidgetItem::setData(role, data);
    notify();
}

void Cell::notify() {
    for (const auto ob:observers)
        ob->update();
}

void Cell::subscribe(Observer *o) {
    observers.push_back(o);
}

void Cell::unsubscribe(Observer *o) {
    observers.remove(o);
}