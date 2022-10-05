//
// Created by peter on 2022/10/4.
//

#include "../include/LinkedMap.h"
#include "../include/rml_debug_out.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


struct rml_LinkedMapItem {
    char *key_;
    void *value_;
    struct rml_LinkedMapItem *pre_;
    struct rml_LinkedMapItem *next_;
};

struct rml_LinkedMap {
    struct rml_LinkedMapItem *head_;
    struct rml_LinkedMapItem *tail_;
    uint64_t length_;
};

static struct rml_LinkedMapItem *rml_LinkedMapItemCreate() {
    struct rml_LinkedMapItem *item = malloc(sizeof(struct rml_LinkedMapItem));
    item->value_ = NULL;
    item->key_ = NULL;
    item->pre_ = NULL;
    item->next_ = NULL;
    return item;
}

static void rml_LinkedMapItemDestroy(struct rml_LinkedMapItem *item) {
    free(item);
}

void *LinkedMapCreate() {
    struct rml_LinkedMap *map = malloc(sizeof(struct rml_LinkedMap));

    map->head_ = rml_LinkedMapItemCreate();
    map->tail_ = rml_LinkedMapItemCreate();
    map->length_ = 0;

    RML_DEBUG("Run LinkedMapCreate")
    return map;
}

void LinkedMapDestroy(void *self) {
    struct rml_LinkedMap *m = self;
    rml_LinkedMapItemDestroy(m->head_);
    rml_LinkedMapItemDestroy(m->tail_);
    free(m);

    RML_DEBUG("Run LinkedMapDestroy")
}

void LinkedMapPut(char *key, void *value) {
    struct rml_LinkedMapItem *newItem = rml_LinkedMapItemCreate();
    newItem->key_ = key;
    newItem->value_ = value;
    // TODO
}