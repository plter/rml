//
// Created by peter on 2022/10/6.
//
#include <rmlLinkedList.h>
#include <rml_debug_out.h>
#include <stdlib.h>

void eachCallback(void *list, void *value, void *attachment) {
    RML_INFO("%s", (char *) value)
}


int main() {

    void *list = rmlLinkedListCreate();
    rmlLinkedListPush(list, "C");
    rmlLinkedListPush(list, "C++");
    rmlLinkedListPush(list, "Python");
    rmlLinkedListPush(list, "JavaScript");
    rmlLinkedListPush(list, "TypeScript");
    rmlLinkedListPush(list, "C#");
    rmlLinkedListPush(list, "Rust");
    rmlLinkedListPop(list);
    rmlLinkedListShift(list);
    rmlLinkedListRemove(list, 1);

    rmlLinkedListEach(list, &eachCallback, NULL);

    RML_INFO("Value at index 2: %s", (char *) rmlLinkedListGet(list, 2));

    rmlLinkedListDestroy(list);
    return 0;
}