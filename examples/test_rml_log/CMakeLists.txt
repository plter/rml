set(CMAKE_C_STANDARD 11)

add_compile_definitions(RML_LOG_LEVEL=1)
include_directories(../../rmlcore/include)
link_libraries(rmlcore)
add_executable(test_rml_log main.c)