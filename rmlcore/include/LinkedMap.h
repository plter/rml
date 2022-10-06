//
// Created by peter on 2022/10/4.
//

#ifndef RML_LINKEDMAP_H
#define RML_LINKEDMAP_H

#include <stdint.h>

typedef void(*LinkedMapEachCallback)(void *linkedMap, char *key, void *value);

void *LinkedMapCreate();

/**
 * LinkedMap dose not destroy values, you should destroy your values as you need before you destroy the LinkedMap
 *
 * @param self
 */
void LinkedMapDestroy(void *self);

/**
 * Put key-value to the map, and return the value
 *
 * @param self
 * @param key
 * @param value
 * @return
 */
void *LinkedMapPut(void *self, char *key, void *value);

/**
 * Remove and return a value by key, return NULL if the value dose not exists
 *
 * @param self
 * @param key
 * @return
 */
void *LinkedMapRemove(void *self, char *key);

int64_t LinkedMapGetLength(void *self);

/**
 * You'd better do not change values of this LinkedMap when you executing this function
 *
 * @param self
 * @param callback
 */
void LinkedMapEach(void *self, LinkedMapEachCallback callback);

#endif //RML_LINKEDMAP_H
