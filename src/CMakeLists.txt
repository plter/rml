cmake_minimum_required(VERSION 3.5)
project(rml)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(./)

set(SOURCE_FILES
        RMLReader.cpp
        RMLCall.cpp
        RMLFunc.cpp
        context/Context.cpp
        context/ArgContext.cpp
        context/FuncContext.cpp
        context/NSContext.cpp
        lang/NS.cpp
        RMLLibrary.cpp
        RMLValue.cpp
        funcs/PrintFunc.cpp)

add_library(rml SHARED ${SOURCE_FILES})