//
// Created by peter on 2022/10/4.
//

#ifndef RML_RMLLINKEDLIST_H
#define RML_RMLLINKEDLIST_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    /**
     * User data
     */
    void *attachment;
    /**
     * The value
     */
    void *value;
    /**
     * The value wrapper
     */
    void *valueItem;
    /**
     * The target LinkedList
     */
    void *linkedList;

    int64_t index;
} rmlLinkedListEachCallbackContext;

/**
 * Return true if you want to break the loop
 */
typedef bool (*rmlLinkedListEachCallback)(rmlLinkedListEachCallbackContext *context);

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
 * Remove item and return it's value, return NULL if the item is NULL or the item not in the list
 * @param item
 */
void *rmlLinkedListRemoveItem(void *self, void *item);

/**
 * You'd better do not change values of this LinkedMap when you executing this function
 *
 * @param self
 * @param callback
 */
void rmlLinkedListEach(void *self, rmlLinkedListEachCallback callback, void *attachment);

/**
 * Return NULL if the item is NULL
 * @param item
 * @return
 */
void *rmlLinkedListItemGetValue(void *item);

#endif //RML_RMLLINKEDLIST_H
