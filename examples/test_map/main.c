//
// Created by peter on 2022/10/7.
//

#include <rmlMap.h>
#include "rml_debug_out.h"

int main() {
    void *map = rmlMapCreate();
    rmlMapPut(map, "name", "C Language");
    rmlMapPut(map, "age", "30");
    RML_INFO("Map size: %lld",rmlMapGetLength(map))
    RML_INFO("name=%s, age=%s", (char *) rmlMapGet(map, "name"), (char *) rmlMapGet(map, "age"))
    RML_INFO("Remove name >>>>>>>")
    rmlMapRemove(map, "name");
    RML_INFO("<<<<<<<<<<<<<<<<<<<")
    rmlMapDestroy(map);
    return 0;
}