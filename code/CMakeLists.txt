cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/KotlinCMakeModule)

project(code Kotlin)

konanc_executable(
        NAME HelloWorld
        SOURCES
        tools/readFile.kt
        rml/XMLReader.kt
        rml/Scope.kt
        rml/Var.kt
        rml/Arg.kt
        rml/funcs/Print.kt
        rml/CommonLib.kt
        rml/Call.kt
        rml/Func.kt
        rml/Application.kt
        rml/RMLReader.kt
        examples/helloworld/hello.kt
)

konanc_executable(
        NAME reader
        SOURCES
        tools/readFile.kt
        rml/XMLReader.kt
        examples/reader/reader.kt
)