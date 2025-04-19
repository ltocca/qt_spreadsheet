//
// Created by leo on 19/04/25.
//
#ifndef QT_SPREADSHEET_OBSERVERMOCK_H
#define QT_SPREADSHEET_OBSERVERMOCK_H

#include <gmock/gmock.h>
#include "../src/Observer.h"

class ObserverMock final : public Observer { // we need to override the Observer's virtual method
public:
    MOCK_METHOD(void, update, (), (override));
};

#endif // QT_SPREADSHEET_OBSERVERMOCK_H