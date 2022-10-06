//
// Created by peter on 2022/10/6.
//

#include <LinkedMap.h>
#include <stdio.h>

void printValue(void *map, char *key, void *value) {
    printf("%s = %s\n", key, (char *) value);
}

int main() {

    void *map = LinkedMapCreate();
    LinkedMapPut(map, "name", "C Language");
    LinkedMapPut(map, "age", "30");
    LinkedMapPut(map, "gender", "male");
    printf("Length: %lld\n", LinkedMapGetLength(map));

    LinkedMapRemove(map, "age");
    printf("Length: %lld\n", LinkedMapGetLength(map));

    LinkedMapRemove(map, "age");
    printf("Length: %lld\n", LinkedMapGetLength(map));

    LinkedMapEach(map, &printValue);

    LinkedMapDestroy(map);
    return 0;
}