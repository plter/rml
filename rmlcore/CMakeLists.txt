set(CMAKE_C_STANDARD 11)

add_library(
        rmlcore
        source/rmlcore.c
        source/rmlLinkedList.c
        source/rmlLinkedMap.c
        source/time_utils.c
        source/key_utils.c
)