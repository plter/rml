set(CMAKE_C_STANDARD 11)

add_library(
        rmlcore
        source/rmlLinkedList.c
        source/time_utils.c
        source/key_utils.c
        source/rmlMap.c
        source/rmlLinkedMap.c
)