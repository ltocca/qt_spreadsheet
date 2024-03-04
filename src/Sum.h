#ifndef QT_SPREADSHEET_SUM_H
#define QT_SPREADSHEET_SUM_H

#include "Formula.h"

class Sum: public Formula {
public:
    double calc() override;
};


#endif //QT_SPREADSHEET_SUM_H
