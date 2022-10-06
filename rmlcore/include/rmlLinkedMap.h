//
// Created by peter on 2022/10/4.
//

#ifndef RML_RMLLINKEDMAP_H
#define RML_RMLLINKEDMAP_H

#include <stdint.h>

typedef void(*LinkedMapEachCallback)(void *linkedMap, char *key, void *value);

void *rmlLinkedMapCreate();

/**
 * LinkedMap dose not destroy values, you should destroy your values as you need before you destroy the LinkedMap
 *
 * @param self
 */
void rmlLinkedMapDestroy(void *self);

/**
 * Put key-value to the map, and return the value
 *
 * @param self
 * @param key
 * @param value
 * @return
 */
void *rmlLinkedMapPut(void *self, char *key, void *value);

/**
 * Remove and return a value by key, return NULL if the value dose not exists
 *
 * @param self
 * @param key
 * @return
 */
void *rmlLinkedMapRemove(void *self, char *key);

int64_t rmlLinkedMapGetLength(void *self);

/**
 * You'd better do not change values of this LinkedMap when you executing this function
 *
 * @param self
 * @param callback
 */
void rmlLinkedMapEach(void *self, LinkedMapEachCallback callback);

#endif //RML_RMLLINKEDMAP_H
