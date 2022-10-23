//
// Created by peter on 2022/10/6.
//

#include <rmlLinkedMap.h>
#include <rml_log.h>
#include <stdio.h>
#include <string.h>

bool printValue(rmlLinkedMapEachCallbackContext *context) {
    RML_INFO("%s = %s", context->key, (char *) context->value);
    return false;
}

int main() {

    void *map = rmlLinkedMapCreate();
    rmlLinkedMapPut(map, "age", "30");
    rmlLinkedMapPut(map, "name", "C Language");
    rmlLinkedMapPut(map, "gender", "male");
    RML_INFO("Length: %lld", rmlLinkedMapGetLength(map));

    rmlLinkedMapRemove(map, "age");
    RML_INFO("Length: %lld", rmlLinkedMapGetLength(map));

    rmlLinkedMapRemove(map, "age");
    RML_INFO("Length: %lld", rmlLinkedMapGetLength(map));

    rmlLinkedMapEach(map, &printValue, NULL);

    rmlLinkedMapDestroy(map);
    return 0;
}