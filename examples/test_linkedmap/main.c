//
// Created by peter on 2022/10/6.
//

#include <LinkedMap.h>
#include <rml_debug_out.h>
#include <stdio.h>

void printValue(void *map, char *key, void *value) {
    RML_INFO("%s = %s", key, (char *) value);
}

int main() {

    void *map = LinkedMapCreate();
    LinkedMapPut(map, "name", "C Language");
    LinkedMapPut(map, "age", "30");
    LinkedMapPut(map, "gender", "male");
    RML_INFO("Length: %lld", LinkedMapGetLength(map));

    LinkedMapRemove(map, "age");
    RML_INFO("Length: %lld", LinkedMapGetLength(map));

    LinkedMapRemove(map, "age");
    RML_INFO("Length: %lld", LinkedMapGetLength(map));

    LinkedMapEach(map, &printValue);

    LinkedMapDestroy(map);
    return 0;
}