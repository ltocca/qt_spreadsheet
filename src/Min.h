#ifndef QT_SPREADSHEET_MIN_H
#define QT_SPREADSHEET_MIN_H
#include "Formula.h"


class Min : public Formula {
public:
    double calc() override;
};

#endif //QT_SPREADSHEET_MIN_H
