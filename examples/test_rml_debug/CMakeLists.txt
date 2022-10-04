set(CMAKE_C_STANDARD 11)

add_compile_definitions(RML_DEBUG=1)
include_directories(../../rmlcore/include)
add_executable(test_rml_debug main.c)