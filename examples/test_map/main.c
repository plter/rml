//
// Created by peter on 2022/10/7.
//

#include <rmlMap.h>
#include "rml_log.h"
#include <string.h>

int main() {
    void *map = rmlMapCreate();
    rmlMapPut(map, "name", "C Language");
    rmlMapPut(map, "age", "30");
    rmlMapPut(map, "age1", "30");

    for (int i = 0; i < 3000; ++i) {
        char key[100];
        memset(key, 0, 100);
        sprintf(key, "item%d", i);
        rmlMapPut(map, key, NULL);
    }

    RML_INFO("Map size: %lld", rmlMapGetLength(map))
    RML_INFO("name=%s, age=%s", (char *) rmlMapGet(map, "name"), (char *) rmlMapGet(map, "age"))
    int64_t size = rmlMapGetLinearSpaceSize(map);
    RML_INFO("rmlMap linear space size: %lld", size)
    RML_INFO("Remove name >>>>>>>")
    rmlMapRemove(map, "name");
    RML_INFO("<<<<<<<<<<<<<<<<<<<")
    rmlMapDestroy(map);
    return 0;
}