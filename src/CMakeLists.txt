cmake_minimum_required(VERSION 3.5)
project(rml)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(./)

set(SOURCE_FILES
        Reader.cpp Reader.h
        IReaderDelegate.h
        parser/ParsePhase.cpp parser/ParsePhase.h
        parser/FuncPhase.cpp parser/FuncPhase.h
        middlecode/MiddleCode.cpp middlecode/MiddleCode.h middlecode/Func.cpp middlecode/Func.h)

add_library(rml SHARED ${SOURCE_FILES})