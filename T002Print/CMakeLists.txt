cmake_minimum_required(VERSION 3.5)
project(rml)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../rml)
link_libraries(rml)

set(SOURCE_FILES T002Print.cpp)
add_executable(Print ${SOURCE_FILES})