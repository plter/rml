cmake_minimum_required(VERSION 3.17)
project(rml C)

add_compile_definitions(RML_LOG_LEVEL=3)

add_subdirectory(rmlcore)
add_subdirectory(examples/helloworld)
add_subdirectory(examples/test_rml_log)
add_subdirectory(examples/test_get_current_local_time)
add_subdirectory(examples/test_encode_key)
add_subdirectory(examples/test_linkedmap)
add_subdirectory(examples/test_linkedlist)
add_subdirectory(examples/test_map)