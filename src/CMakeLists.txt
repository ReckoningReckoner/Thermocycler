# This is for the unit tests only
cmake_minimum_required(VERSION 3.6)
project(Thermocycler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(TEST_FILES
    src/constants.h
    src/Cycles.cpp
    src/Cycles.h
    test/CycleTests.cpp
    test/Tests.cpp 
    test/CycleTests.h
    src/Interface.cpp
    src/Interface.h)

add_executable(unittest ${TEST_FILES})
