cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/KotlinCMakeModule)

project(code Kotlin)

konanc_executable(
        NAME HelloWorld
        SOURCES hello.kt
)

konanc_executable(
        NAME reader
        SOURCES
        tools/readFile.kt
        rml/RMLReader.kt
        examples/reader/reader.kt
)