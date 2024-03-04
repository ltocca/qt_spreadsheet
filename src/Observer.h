
#ifndef QT_SPREADSHEET_OBSERVER_H
#define QT_SPREADSHEET_OBSERVER_H

#include "Subject.h"

class Observer //
{
public:
    virtual ~Observer() = default; // suggested by Clang
    virtual void update() = 0;
    //virtual void attach() = 0;
    //virtual void detach() = 0;
};


#endif //QT_SPREADSHEET_OBSERVER_H
