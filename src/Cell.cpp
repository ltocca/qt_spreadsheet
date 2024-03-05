
#include "Cell.h"

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
    // TODO: when the structure is defined, define update method
}

// getters and setters

const double Cell::getValue() const {
    return value;
}


void Cell::setValue(double v) {
    value = v;
}

const bool Cell::checkCustomValue() const {
    return customValue;
}

void Cell::setCustomValue(bool cv) {
    customValue = cv;
}



