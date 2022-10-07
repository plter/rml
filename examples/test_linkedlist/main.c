//
// Created by peter on 2022/10/6.
//
#include <rmlLinkedList.h>
#include <rml_debug_out.h>

bool eachCallback(rmlLinkedListEachCallbackContext *context) {
    RML_INFO("%s", (char *) context->value)
    return false;
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