cmake_minimum_required(VERSION 3.30)
project(spreadsheet_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Path to the source files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_subdirectory(.lib/googletest)
set(gtest_SOURCE_DIR .lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Test
        REQUIRED)

# Source files from the main project
set(SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Cell.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Formula.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Sum.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Max.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Min.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Mean.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Spreadsheet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/UserInterface.cpp
)

set(    TEST_SOURCE_FILES
        runAllTests.cpp
        SumTest.cpp
        CellTest.cpp
        MeanTest.cpp
        MinTest.cpp
        SpreadsheetTest.cpp
        UITest.cpp
)

add_executable(spreadsheet_test ${TEST_SOURCE_FILES} ${SOURCE_FILES})
target_link_libraries(spreadsheet_test
        gtest
        gtest_main
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Test
)

enable_testing(true)