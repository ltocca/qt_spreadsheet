
#ifndef QT_SPREADSHEET_FORMULA_H
#define QT_SPREADSHEET_FORMULA_H


#include <list>
#include <string>
#include "Cell.h"

class Formula{
public:
    virtual ~Formula()= default;

    virtual double calc() = 0; // calculate method
    const std::list<double>& getElements() const;
    const std::string &getDefinition() const;

    void setElements(const std::list<double> &elements);
    void setDefinition(const std::string &definition);

protected:
    std::list<double> elements; // list of elements
    std::string definition;
};


#endif //QT_SPREADSHEET_FORMULA_H
