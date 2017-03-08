# This is for the unit tests only
cmake_minimum_required(VERSION 3.6)
project(Thermocycler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(TEST_FILES
    ../src/constants.h
    ../src/Cycles.cpp
    ../src/Cycles.h
    ../src/Interface.cpp
    ../src/Interface.h
    Tests.cpp 
    CycleTests.cpp
    CycleTests.h)

add_executable(unittest ${TEST_FILES})
