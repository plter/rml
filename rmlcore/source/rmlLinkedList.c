//
// Created by peter on 2022/10/4.
//

#include "../include/rmlLinkedList.h"
#include "../include/rml_debug_out.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct rmlLinkedListItem {
    void *value_;
    struct rmlLinkedListItem *pre_;
    struct rmlLinkedListItem *next_;
};

struct rmlLinkedList {
    struct rmlLinkedListItem *head_;
    struct rmlLinkedListItem *tail_;
    uint64_t length_;
};

static void rmlLinkedListItemReset(struct rmlLinkedListItem *item) {
    item->value_ = NULL;
    item->pre_ = NULL;
    item->next_ = NULL;
}

static struct rmlLinkedListItem *rml_LinkedListItemCreate() {
    struct rmlLinkedListItem *item = malloc(sizeof(struct rmlLinkedListItem));
    rmlLinkedListItemReset(item);
    RML_DEBUG("Create LinkedListItem");
    return item;
}

static void rmlLinkedListItemDestroy(struct rmlLinkedListItem *item) {
    if (item != NULL) {
        rmlLinkedListItemReset(item);
        free(item);

        RML_DEBUG("Destroy LinkedListItem");
    }
}

/**
 * Just reset properties, do not free tail or head
 *
 * @param self
 */
static void rmlLinkedListReset(struct rmlLinkedList *self) {
    self->tail_ = NULL;
    self->head_ = NULL;
    self->length_ = 0;
}

void *rmlLinkedListCreate() {
    struct rmlLinkedList *map = malloc(sizeof(struct rmlLinkedList));
    rmlLinkedListReset(map);

    RML_DEBUG("Create LinkedList")
    return map;
}

void rmlLinkedListDestroy(void *self) {
    struct rmlLinkedList *m = self;

    while (rmlLinkedListGetLength(self)) {
        rmlLinkedListPop(self);
    }

    rmlLinkedListReset(self);
    free(m);

    RML_DEBUG("Destroy LinkedList")
}


/**
 * Return NULL if index out of range
 *
 * @param self
 * @param index
 * @return
 */
static struct rmlLinkedListItem *rmlLinkedListGetItem_(struct rmlLinkedList *self, int64_t index) {
    if (self->head_ == NULL || self->tail_ == NULL) {
        return NULL;
    }

    int64_t length = rmlLinkedListGetLength(self);
    int64_t position = 0;
    struct rmlLinkedListItem *current;
    if (index <= length / 2) {
        position = 0;
        for (current = self->head_; current != NULL; current = current->next_) {
            if (position == index) {
                return current;
            }
            position++;
        }
    } else {
        position = length - 1;
        for (current = self->tail_; current != NULL; current = current->pre_) {
            if (position == index) {
                return current;
            }
            position--;
        }
    }

    return NULL;
}


void *rmlLinkedListPush(void *self, void *value) {
    struct rmlLinkedListItem *newItem = rml_LinkedListItemCreate();
    newItem->value_ = value;

    struct rmlLinkedList *selfList = self;
    if (selfList->tail_ != NULL) {
        newItem->pre_ = selfList->tail_;
        selfList->tail_->next_ = newItem;
        selfList->tail_ = newItem;
    } else {
        // If tail is NULL, it means we are adding the first item
        selfList->head_ = newItem;
        selfList->tail_ = newItem;
    }
    selfList->length_++;
    return value;
}

void *rmlLinkedListRemove(void *self, int64_t index) {
    struct rmlLinkedListItem *item = rmlLinkedListGetItem_(self, index);
    if (item == NULL) {
        return NULL;
    }
    rmlLinkedListRemoveItem(self, item);
    return item->value_;
}

int64_t rmlLinkedListGetLength(void *self) {
    return ((struct rmlLinkedList *) self)->length_;
}


void *rmlLinkedListPop(void *self) {
    struct rmlLinkedList *selfList = self;
    if (selfList->tail_ == NULL) {
        return NULL;
    }

    struct rmlLinkedListItem *pendingDestroyItem = selfList->tail_;
    selfList->tail_ = selfList->tail_->pre_;
    if (selfList->tail_ != NULL) {
        selfList->tail_->next_ = NULL;
    }
    selfList->length_--;
    void *value = pendingDestroyItem->value_;
    rmlLinkedListItemDestroy(pendingDestroyItem);
    return value;
}

void *rmlLinkedListShift(void *self) {
    struct rmlLinkedList *selfList = self;
    if (selfList->head_ == NULL) {
        return NULL;
    }

    struct rmlLinkedListItem *pendingDestroyItem = selfList->head_;
    selfList->head_ = selfList->head_->next_;
    if (selfList->head_ != NULL) {
        selfList->head_->pre_ = NULL;
    }
    selfList->length_--;
    void *value = pendingDestroyItem->value_;
    rmlLinkedListItemDestroy(pendingDestroyItem);
    return value;
}


void rmlLinkedListEach(void *self, rmlLinkedListEachCallback callback, void *attachment) {
    struct rmlLinkedList *selfList = self;
    rmlLinkedListEachCallbackContext context;
    context.linkedList = selfList;
    context.attachment = attachment;
    for (struct rmlLinkedListItem *current = selfList->head_; current != NULL; current = current->next_) {
        if (callback == NULL) {
            break;
        }

        context.valueItem = current;
        context.value = current->value_;
        if (callback(&context)) {
            break;
        }
    }
}

void *rmlLinkedListGet(void *self, int64_t index) {
    struct rmlLinkedListItem *item = rmlLinkedListGetItem_(self, index);
    return item != NULL ? item->value_ : NULL;
}

void rmlLinkedListRemoveItem(void *self, void *item) {
    if (item == NULL) {
        return;
    }

    struct rmlLinkedListItem *theItem = item;
    if (theItem->pre_ == NULL && theItem->next_ == NULL) {
        return;
    }

    if (theItem->next_ != NULL) {
        theItem->next_->pre_ = theItem->pre_;
    }
    if (theItem->pre_ != NULL) {
        theItem->pre_->next_ = theItem->next_;
    }
    struct rmlLinkedList *selfList = self;
    if (item == selfList->head_) {
        selfList->head_ = theItem->next_;
    }
    if (item == selfList->tail_) {
        selfList->tail_ = theItem->pre_;
    }
    selfList->length_--;
    rmlLinkedListItemDestroy(item);
}

void *rmlLinkedListItemGetValue(void *item) {
    if (item == NULL) {
        return NULL;
    }
    return ((struct rmlLinkedListItem *) item)->value_;
}