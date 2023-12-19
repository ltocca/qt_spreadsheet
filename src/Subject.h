
#ifndef QT_SPREADSHEET_SUBJECT_H
#define QT_SPREADSHEET_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual ~Subject()= default;
    virtual void notify() = 0;
    virtual void subscribe(Observer* o) = 0;
    virtual void unsubscribe(Observer* o) = 0;
};

#endif //QT_SPREADSHEET_SUBJECT_H
