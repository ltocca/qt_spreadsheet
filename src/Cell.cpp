#include "Cell.h"

// Constructor and destructor

/*Cell::Cell(double v) : QTableWidgetItem(){
    value.setValue(v);
}*/

// Observer and Subject

void Cell::subscribe(Observer *o) {
    observers.push_back(o);
}

void Cell::unsubscribe(Observer *o) {
    observers.remove(o);
}

void Cell::notify() {
    for (auto observer : observers) {
        observer->update();
    }
}

void Cell::update() {
    // TODO: when the structure is defined, define update method, need to update every value
}

// getters and setters

double Cell::getValue() const { // not sure if it is correct
    return value.value<double>();
}


void Cell::setValue(double v) {
    value.setValue<double>(v);
    customValue = true;
    notify(); // need to notify every subscribed cell
}

bool Cell::checkCustomValue() const {
    return customValue;
}

void Cell::setCustomValue(bool cv) {
    customValue = cv;
}

void Cell::addCell(Cell& c) {
    cellSelection.push_back(c); //TODO FIXIT
}

void Cell::selectCells(std::list<std::shared_ptr<Cell>> cs) {
    cellSelection = cs;
}


std::list<double> extractValues(std::list<std::shared_ptr<Cell>>& cs) {
    std::list<double> selectedValues;
    for (const auto& cell : cs) {
        selectedValues.push_back(cell->getValue());
    }
    return selectedValues;
}
