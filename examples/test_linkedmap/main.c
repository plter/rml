//
// Created by peter on 2022/10/6.
//

#include <rmlLinkedMap.h>
#include <rml_debug_out.h>
#include <stdio.h>

void printValue(void *map, char *key, void *value) {
    RML_INFO("%s = %s", key, (char *) value);
}

int main() {

    void *map = rmlLinkedMapCreate();
    rmlLinkedMapPut(map, "name", "C Language");
    rmlLinkedMapPut(map, "age", "30");
    rmlLinkedMapPut(map, "gender", "male");
    RML_INFO("Length: %lld", rmlLinkedMapGetLength(map));

    rmlLinkedMapRemove(map, "age");
    RML_INFO("Length: %lld", rmlLinkedMapGetLength(map));

    rmlLinkedMapRemove(map, "age");
    RML_INFO("Length: %lld", rmlLinkedMapGetLength(map));

    rmlLinkedMapEach(map, &printValue);

    rmlLinkedMapDestroy(map);
    return 0;
}