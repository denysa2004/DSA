cmake_minimum_required(VERSION 3.28)
project(lab5dsa)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab5dsa
        SortedSetIterator.h
        SortedSetIterator.cpp
        SortedSet.cpp
        ShortTest.h
        ShortTest.cpp
        ExtendedTest.h
        ExtendedTest.cpp
        App.cpp)
