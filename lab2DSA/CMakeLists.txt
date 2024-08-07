cmake_minimum_required(VERSION 3.27)
project(lab_2_dsa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_2_dsa
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ListIterator.cpp
        ListIterator.h
        ShortTest.cpp
        ShortTest.h
        SortedIteratedList.cpp
        SortedIteratedList.h)
