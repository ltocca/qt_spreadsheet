cmake_minimum_required(VERSION 3.30)
project(qt_spreadsheet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt_spreadsheet main.cpp
        src/Observer.h
        src/Subject.h
        src/Formula.cpp
        src/Formula.h
        src/Cell.cpp
        src/Cell.h
        src/Max.cpp
        src/Max.h
        src/Min.cpp
        src/Min.h
        src/Mean.cpp
        src/Mean.h
        src/Sum.cpp
        src/Sum.h
        src/Spreadsheet.cpp
        src/Spreadsheet.h
        src/UserInterface.cpp
        src/UserInterface.h)
target_link_libraries(qt_spreadsheet
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

