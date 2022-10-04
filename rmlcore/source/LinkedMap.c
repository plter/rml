//
// Created by peter on 2022/10/4.
//

#include "LinkedMap.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


struct rml_LinkedMapItem {
    char *name_;
    void *value_;
    struct rml_LinkedMapItem *pre_;
    struct rml_LinkedMapItem *next_;
};

struct rml_LinkedMap {
    struct rml_LinkedMapItem *begin_;
    struct rml_LinkedMapItem *end_;
    uint64_t length_;
};

void *LinkedMapCreate() {
    struct rml_LinkedMap *map = malloc(sizeof(struct rml_LinkedMap));
    return map;
}

void LinkedMapDestroy(void *self) {
    free(self);
}