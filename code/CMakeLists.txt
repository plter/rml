cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/KotlinCMakeModule)

project(code Kotlin)

add_subdirectory(examples/helloworld)
add_subdirectory(examples/array)
add_subdirectory(examples/callto)
add_subdirectory(examples/ref)
add_subdirectory(examples/reader)
add_subdirectory(examples/map)
add_subdirectory(examples/oo)