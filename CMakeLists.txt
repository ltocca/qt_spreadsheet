cmake_minimum_required(VERSION 3.25)
project(qt_spreadsheet)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt_spreadsheet main.cpp src/Cell.cpp src/Cell.h src/Observer.h src/Subject.h src/Mean.cpp src/Mean.h src/Max.cpp src/Max.h src/Min.cpp src/Min.h src/Sum.cpp src/Sum.h src/Formula.cpp src/Formula.h)
target_link_libraries(qt_spreadsheet
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

