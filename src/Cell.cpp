#include "Cell.h"

#include "Formula.h"


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

void Cell::setFormula(Formula *formula) {
    insertedFormula = formula;
    setBackground(QBrush(formula->getColor()));
}

Formula * Cell::getFormula() const {
    return insertedFormula;
}

bool Cell::hasFormula() const {
    bool f = false;
    if (insertedFormula != nullptr) {
        f = true;
    }
    return f;
}

void Cell::resetCell(){
    setData(0, 0);
    setBackground(QBrush(QColor(255, 255, 255))); // reset cell color
    observers.clear();

}

void Cell::notify() {
    if (!observers.empty()) {
        for (const auto ob:observers)
            ob->update();
    }
}

void Cell::subscribe(Observer *o) {
    observers.push_back(o);
}

void Cell::unsubscribe(Observer *o) {
    observers.remove(o);
}