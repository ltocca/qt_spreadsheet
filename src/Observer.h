//
// Created by leo on 07/02/25.
//

#ifndef QT_SPREADSHEET_OBSERVER_H
#define QT_SPREADSHEET_OBSERVER_H

class Observer {
public:
    virtual ~Observer() = default; // Suggested by Clang to define a trivial destructor

    virtual void update() = 0;
    //virtual void attach() = 0;
    //virtual void detach() = 0;
};

#endif //QT_SPREADSHEET_OBSERVER_H
