set(CMAKE_C_STANDARD 11)

include_directories(../../rmlcore/include)
link_libraries(rmlcore)
add_executable(test_linkedmap main.c)