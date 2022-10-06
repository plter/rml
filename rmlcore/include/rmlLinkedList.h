//
// Created by peter on 2022/10/4.
//

#ifndef RML_RMLLINKEDLIST_H
#define RML_RMLLINKEDLIST_H

#include <stdint.h>

typedef void(*LinkedListEachCallback)(void *linkedMap, void *value, void *attachment);

void *rmlLinkedListCreate();

/**
 * LinkedMap dose not destroy values, you should destroy your values as you need before you destroy the LinkedMap
 *
 * @param self
 */
void rmlLinkedListDestroy(void *self);

/**
 * Put key-value to the map, and return the value
 *
 * @param self
 * @param key
 * @param value
 * @return
 */
void *rmlLinkedListPush(void *self, void *value);

/**
 * Remove and return a value by key, return NULL if the value dose not exists
 *
 * @param self
 * @param key
 * @return
 */
void *rmlLinkedListRemove(void *self, int64_t index);

void *rmlLinkedListPop(void *self);

void *rmlLinkedListShift(void *self);

void *rmlLinkedListGet(void *self, int64_t index);

int64_t rmlLinkedListGetLength(void *self);

/**
 * You'd better do not change values of this LinkedMap when you executing this function
 *
 * @param self
 * @param callback
 */
void rmlLinkedListEach(void *self, LinkedListEachCallback callback, void *attachment);

#endif //RML_RMLLINKEDLIST_H
