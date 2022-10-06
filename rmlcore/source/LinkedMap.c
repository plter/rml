//
// Created by peter on 2022/10/4.
//

#include "../include/LinkedMap.h"
#include "../include/rml_debug_out.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct rml_LinkedMapItem {
    char *key_;
    void *value_;
    struct rml_LinkedMapItem *pre_;
    struct rml_LinkedMapItem *next_;
};

struct rml_LinkedMap {
    struct rml_LinkedMapItem *anchor_;
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
    if (item != NULL) {
        free(item);
    }
}

void *LinkedMapCreate() {
    struct rml_LinkedMap *map = malloc(sizeof(struct rml_LinkedMap));

    map->anchor_ = NULL;
    map->length_ = 0;

    RML_DEBUG("Run LinkedMapCreate")
    return map;
}

void LinkedMapDestroy(void *self) {
    struct rml_LinkedMap *m = self;

    struct rml_LinkedMapItem *item = m->anchor_;
    struct rml_LinkedMapItem *tmp;
    while (item != NULL) {
        tmp = item;
        item = item->next_;
        rml_LinkedMapItemDestroy(tmp);
    }

    free(m);

    RML_DEBUG("Run LinkedMapDestroy")
}

static struct rml_LinkedMapItem *LinkedMapGetItem_(struct rml_LinkedMap *self, char *key) {
    if (self->anchor_ == NULL) {
        return NULL;
    }

    struct rml_LinkedMapItem *current = self->anchor_;
    do {
        if (strcmp(current->key_, key) != 0) {
            current = current->next_;
        } else {
            return current;
        }
    } while (current != NULL);

    return NULL;
}

/**
 * Just append, do not check duplicated
 * @param self
 * @param key
 * @param value
 */
static void LinkedMapAppend(struct rml_LinkedMap *self, char *key, void *value) {
    struct rml_LinkedMapItem *newItem = rml_LinkedMapItemCreate();
    newItem->key_ = key;
    newItem->value_ = value;

    if (self->anchor_ != NULL) {
        self->anchor_->pre_ = newItem;
        newItem->next_ = self->anchor_;
    }

    self->anchor_ = newItem;
    self->length_++;
}

void *LinkedMapPut(void *self, char *key, void *value) {
    struct rml_LinkedMapItem *item = LinkedMapGetItem_(self, key);
    if (item == NULL) {
        LinkedMapAppend(self, key, value);
    } else {
        item->value_ = value;
    }
    return value;
}

void *LinkedMapRemove(void *self, char *key) {
    struct rml_LinkedMapItem *item = LinkedMapGetItem_(self, key);
    if (item == NULL) {
        return NULL;
    }
    if (item->next_ != NULL) {
        item->next_->pre_ = item->pre_;
    }
    if (item->pre_ != NULL) {
        item->pre_->next_ = item->next_;
    }
    struct rml_LinkedMap *selfMap = self;
    if (item == selfMap->anchor_) {
        selfMap->anchor_ = item->next_;
    }
    selfMap->length_--;
    item->next_ = NULL;
    item->pre_ = NULL;
    rml_LinkedMapItemDestroy(item);
    return item->value_;
}

int64_t LinkedMapGetLength(void *self) {
    return ((struct rml_LinkedMap *) self)->length_;
}

void LinkedMapEach(void *self, LinkedMapEachCallback callback) {
    struct rml_LinkedMap *selfMap = self;
    struct rml_LinkedMapItem *item = selfMap->anchor_;
    while (item != NULL) {
        if (callback != NULL) {
            callback(self, item->key_, item->value_);
        }
        item = item->next_;
    }
}