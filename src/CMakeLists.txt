cmake_minimum_required(VERSION 3.6)
project(Thermocycler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(TEST_FILES
    sketch/constants.h
    sketch/Cycles.cpp
    sketch/Cycles.h
    test/CycleTests.cpp
    test/Tests.cpp 
    test/CycleTests.h
    sketch/Interface.cpp
    sketch/Interface.h)

add_executable(unittest ${TEST_FILES})
