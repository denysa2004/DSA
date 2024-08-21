cmake_minimum_required(VERSION 3.27)
project(lab1_dsa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab1_dsa
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Map.cpp
        Map.h
        MapIterator.cpp
        MapIterator.h
        ShortTest.cpp
        ShortTest.h)
