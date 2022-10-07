//
// Created by peter on 2022/10/7.
//

#ifndef RML_RMLLINKEDMAP_H
#define RML_RMLLINKEDMAP_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    void *map;
    char *key;
    void *value;
    void *attachment;
} rmlLinkedMapEachCallbackContext;

typedef bool(*rmlLinkedMapEachCallback)(rmlLinkedMapEachCallbackContext *context);

void *rmlLinkedMapCreate();

void *rmlLinkedMapPut(void *self, char *key, void *value);

/**
 * Remove and return the value if it exists, or return NULL
 *
 * @param self
 * @param key
 * @return
 */
void *rmlLinkedMapRemove(void *self, char *key);

int64_t rmlLinkedMapGetLength(void *self);

void *rmlLinkedMapGet(void *self, char *key);

void rmlLinkedMapDestroy(void *self);

void rmlLinkedMapEach(void *self, rmlLinkedMapEachCallback callback, void *attachment);

#endif //RML_RMLLINKEDMAP_H
