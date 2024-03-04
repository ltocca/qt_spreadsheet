#ifndef QT_SPREADSHEET_MAX_H
#define QT_SPREADSHEET_MAX_H

#include "Formula.h"

class Max: public Formula {
public:
    double calc() override;
};

#endif //QT_SPREADSHEET_MAX_H
