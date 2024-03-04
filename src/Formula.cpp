
#include "Formula.h"
#include "Cell.h"

const std::list<double> & Formula::getElements() const {
    return elements;
}

const std::string & Formula::getDefinition() const {
    return definition;
}

void Formula::setElements(const std::list<double> &elements) {
    Formula::elements = elements;
}

void Formula::setDefinition(const std::string &definition) {
    Formula::definition = definition;
}
