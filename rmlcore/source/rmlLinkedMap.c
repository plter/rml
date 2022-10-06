//
// Created by peter on 2022/10/4.
//

#include "../include/rmlLinkedMap.h"
#include "../include/rml_debug_out.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct rmlLinkedMapItem {
    char *key_;
    void *value_;
    struct rmlLinkedMapItem *pre_;
    struct rmlLinkedMapItem *next_;
};

struct rmlLinkedMap {
    struct rmlLinkedMapItem *anchor_;
    uint64_t length_;
};

static void rmlLinkedMapItemReset(struct rmlLinkedMapItem *item) {
    item->value_ = NULL;
    item->key_ = NULL;
    item->pre_ = NULL;
    item->next_ = NULL;
}

static struct rmlLinkedMapItem *rml_LinkedMapItemCreate() {
    struct rmlLinkedMapItem *item = malloc(sizeof(struct rmlLinkedMapItem));
    rmlLinkedMapItemReset(item);
    return item;
}

static void rmlLinkedMapItemDestroy(struct rmlLinkedMapItem *item) {
    if (item != NULL) {
        rmlLinkedMapItemReset(item);
        free(item);
    }
}

void *rmlLinkedMapCreate() {
    struct rmlLinkedMap *map = malloc(sizeof(struct rmlLinkedMap));

    map->anchor_ = NULL;
    map->length_ = 0;

    RML_DEBUG("Run rmlLinkedMapCreate")
    return map;
}

void rmlLinkedMapDestroy(void *self) {
    struct rmlLinkedMap *m = self;

    struct rmlLinkedMapItem *item = m->anchor_;
    struct rmlLinkedMapItem *tmp;
    while (item != NULL) {
        tmp = item;
        item = item->next_;
        rmlLinkedMapItemDestroy(tmp);
    }

    free(m);

    RML_DEBUG("Run rmlLinkedMapDestroy")
}

static struct rmlLinkedMapItem *LinkedMapGetItem_(struct rmlLinkedMap *self, char *key) {
    if (self->anchor_ == NULL) {
        return NULL;
    }

    struct rmlLinkedMapItem *current = self->anchor_;
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
static void rmlLinkedMapAppend(struct rmlLinkedMap *self, char *key, void *value) {
    struct rmlLinkedMapItem *newItem = rml_LinkedMapItemCreate();
    newItem->key_ = key;
    newItem->value_ = value;

    if (self->anchor_ != NULL) {
        self->anchor_->pre_ = newItem;
        newItem->next_ = self->anchor_;
    }

    self->anchor_ = newItem;
    self->length_++;
}

void *rmlLinkedMapPut(void *self, char *key, void *value) {
    struct rmlLinkedMapItem *item = LinkedMapGetItem_(self, key);
    if (item == NULL) {
        rmlLinkedMapAppend(self, key, value);
    } else {
        item->value_ = value;
    }
    return value;
}

void *rmlLinkedMapRemove(void *self, char *key) {
    struct rmlLinkedMapItem *item = LinkedMapGetItem_(self, key);
    if (item == NULL) {
        return NULL;
    }
    if (item->next_ != NULL) {
        item->next_->pre_ = item->pre_;
    }
    if (item->pre_ != NULL) {
        item->pre_->next_ = item->next_;
    }
    struct rmlLinkedMap *selfMap = self;
    if (item == selfMap->anchor_) {
        selfMap->anchor_ = item->next_;
    }
    selfMap->length_--;
    rmlLinkedMapItemDestroy(item);
    return item->value_;
}

int64_t rmlLinkedMapGetLength(void *self) {
    return ((struct rmlLinkedMap *) self)->length_;
}

void rmlLinkedMapEach(void *self, LinkedMapEachCallback callback) {
    struct rmlLinkedMap *selfMap = self;
    struct rmlLinkedMapItem *item = selfMap->anchor_;
    while (item != NULL) {
        if (callback != NULL) {
            callback(self, item->key_, item->value_);
        }
        item = item->next_;
    }
}