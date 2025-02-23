#pragma once
#include "Observer.h"

#ifndef QT_SPREADSHEET_SUBJECT_H
#define QT_SPREADSHEET_SUBJECT_H

class Subject {
public:
    virtual void notify() = 0;

    virtual void subscribe(Observer *o) = 0;

    virtual void unsubscribe(Observer *o) = 0;

    virtual ~Subject() = default;
};

#endif //QT_SPREADSHEET_SUBJECT_H
