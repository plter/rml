cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/KotlinCMakeModule)

project(code Kotlin)

konanc_executable(
        NAME HelloWorld
        SOURCES
        tools/readFile.kt
        rml/XMLReader.kt
        rml/Scope.kt
        rml/cmds/Command.kt
        rml/cmds/Var.kt
        rml/Arg.kt
        rml/funcs/Print.kt
        rml/CommonLib.kt
        rml/cmds/Call.kt
        rml/Func.kt
        rml/Application.kt
        rml/RMLReader.kt
        examples/helloworld/main.kt
)

konanc_executable(
        NAME callto
        SOURCES
        tools/readFile.kt
        rml/XMLReader.kt
        rml/Scope.kt
        rml/cmds/Command.kt
        rml/cmds/Var.kt
        rml/cmds/Return.kt
        rml/Arg.kt
        rml/funcs/Print.kt
        rml/CommonLib.kt
        rml/cmds/Call.kt
        rml/Func.kt
        rml/Application.kt
        rml/RMLReader.kt
        examples/callto/main.kt
)

konanc_executable(
        NAME ref
        SOURCES
        tools/readFile.kt
        rml/XMLReader.kt
        rml/Scope.kt
        rml/cmds/Command.kt
        rml/cmds/Var.kt
        rml/Arg.kt
        rml/funcs/Print.kt
        rml/CommonLib.kt
        rml/cmds/Call.kt
        rml/Func.kt
        rml/Application.kt
        rml/RMLReader.kt
        examples/ref/ref.kt
)


konanc_executable(
        NAME reader
        SOURCES
        tools/readFile.kt
        rml/XMLReader.kt
        examples/reader/reader.kt
)