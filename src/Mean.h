#ifndef QT_SPREADSHEET_MEAN_H
#define QT_SPREADSHEET_MEAN_H

#include "Formula.h"

class Mean: public Formula {
public:
    double calc() override;
};


#endif //QT_SPREADSHEET_MEAN_H
