cmake_minimum_required(VERSION 3.30)
project(spreadsheet_test)

set(CMAKE_CXX_STANDARD 20)
#[[set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)]]

add_subdirectory(gtest)
set(gtest_SOURCE_DIR gtest/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include) # Assuming you have an 'include' folder

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(spreadsheet_test
        runAllTests.cpp
        MeanTest.cpp
        SumTest.cpp
        MaxTest.cpp
        MinTest.cpp
        SpreadsheetTest.cpp
        UserInterfaceTest.cpp
        CellTest.cpp)
target_link_libraries(spreadsheet_test
        gtest
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)