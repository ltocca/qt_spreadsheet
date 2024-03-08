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
    if (formula) {
        std::list<double> values;
        for (const auto &observedCell : cellSelection) {
            if (observedCell->checkCustomValue())
                values.push_back(observedCell->getValue());
        }
        formula->setElements(values);
        setValue(formula->calc());
    }
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
    auto ptr = std::make_shared<Cell>(c);
    cellSelection.push_back(ptr); //TODO FIXIT
}
void Cell::selectCells(std::list<std::shared_ptr<Cell>> cs) {
    cellSelection = cs;
}

std::list<double> Cell::extractValues(std::list<std::shared_ptr<Cell>>& cs) {
    std::list<double> selectedValues;
    for (const auto& cell : cs) {
        selectedValues.push_back(cell->getValue());
    }
    return selectedValues;
}

void Cell::setFormula(int fType, std::list<std::shared_ptr<Cell>>& involvedCells, const std::string& f) {
    removeFormula();
    std::list<double> cellsValues = extractValues(involvedCells);

    switch(fType) {
        case 0:
            formula = std::make_shared<Sum>();
            formula->setDefinition(f);
            formula->setElements(cellsValues);
            setValue(formula->calc());
            //hasValue = true;
            break;
        case 1:
            formula = std::make_shared<Max>();
            formula->setDefinition(f);
            formula->setElements(cellsValues);
            setValue(formula->calc());
        case 2:
            formula = std::make_shared<Min>();
            formula->setDefinition(f);
            formula->setElements(cellsValues);
            setValue(formula->calc());
        case 3:
            formula = std::make_shared<Mean>();
            formula->setDefinition(f);
            formula->setElements(cellsValues);
            setValue(formula->calc());
            break;
        default:
            break;
    }
}

const std::shared_ptr<Formula>& Cell::getFormula() const {
    return formula;
}

void Cell::removeFormula() {
    formula.reset();
    for (const auto &observedCell : cellSelection) {
        observedCell->unsubscribe(this);
    }
}

void Cell::setData(int role, const QVariant &value) {
    QTableWidgetItem::setData(role, value);
    notify();
}

float Cell::getData() {
    return QTableWidgetItem::data(0).toFloat();
}