//
// Created by peter on 2022/10/7.
//

#include "../include/rmlLinkedMap.h"
#include "../include/rmlLinkedList.h"
#include "../include/rml_debug_out.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct rmlLinkedMapKeyValuePair_ {
    char *key;
    void *value;
};

static struct rmlLinkedMapKeyValuePair_ *rmlLinkedMapKeyValuePairCreate() {
    RML_DEBUG("Create LinkedMap Key-Value pair")
    struct rmlLinkedMapKeyValuePair_ *pair = malloc(sizeof(struct rmlLinkedMapKeyValuePair_));
    pair->value = NULL;
    pair->key = NULL;
    return pair;
}

static void rmlLinkedMapKeyValuePairDestroy(struct rmlLinkedMapKeyValuePair_ *self) {
    if (self != NULL) {
        RML_DEBUG("Destroy LinkedMap Key-Value pair")
        free(self);
    }
}


void *rmlLinkedMapCreate() {
    RML_DEBUG("Create LinkedMap, also create the related LinkedList")
    return rmlLinkedListCreate();
}

void *rmlLinkedMapPut(void *self, char *key, void *value) {
    assert(key != NULL);

    struct rmlLinkedMapKeyValuePair_ *pair = rmlLinkedMapGet(self, key);
    if (pair == NULL) {
        pair = rmlLinkedMapKeyValuePairCreate();
        pair->key = key;
        pair->value = value;
        rmlLinkedListPush(self, pair);
    } else {
        pair->value = value;
    }
    return value;
}


int64_t rmlLinkedMapGetLength(void *self) {
    return rmlLinkedListGetLength(self);
}

struct rmlLinkedMapGetEachCallbackAttachment_ {
    char *key;
    struct rmlLinkedMapKeyValuePair_ *pair;
    void *pairItem;
};

static void rmlLinkedMapGetCallbackAttachment_reset(struct rmlLinkedMapGetEachCallbackAttachment_ *self) {
    self->pair = NULL;
    self->key = NULL;
    self->pairItem = NULL;
}

static bool rmlLinkedMapGetPairItemEachCallback(rmlLinkedListEachCallbackContext *context) {
    struct rmlLinkedMapGetEachCallbackAttachment_ *attachment = context->attachment;
    struct rmlLinkedMapKeyValuePair_ *pair = context->value;
    if (strcmp(pair->key, attachment->key) == 0) {
        attachment->pair = pair;
        attachment->pairItem = context->valueItem;
        return true;
    }
    return false;
}

static void *rmlLinkedMapGetPairItem(void *self, char *key) {
    struct rmlLinkedMapGetEachCallbackAttachment_ attachment;
    rmlLinkedMapGetCallbackAttachment_reset(&attachment);
    attachment.key = key;
    rmlLinkedListEach(self, &rmlLinkedMapGetPairItemEachCallback, &attachment);
    return attachment.pairItem;
}


void *rmlLinkedMapGet(void *self, char *key) {
    struct rmlLinkedMapGetEachCallbackAttachment_ attachment;
    rmlLinkedMapGetCallbackAttachment_reset(&attachment);
    attachment.key = key;
    rmlLinkedListEach(self, &rmlLinkedMapGetPairItemEachCallback, &attachment);
    return attachment.pair != NULL ? attachment.pair->value : NULL;
}

void *rmlLinkedMapRemove(void *self, char *key) {
    void *item = rmlLinkedMapGetPairItem(self, key);
    struct rmlLinkedMapKeyValuePair_ *pair = rmlLinkedListItemGetValue(item);

    void *value = pair != NULL ? pair->value : NULL;

    rmlLinkedMapKeyValuePairDestroy(pair);
    rmlLinkedListRemoveItem(self, item);
    return value;
}

void rmlLinkedMapDestroy(void *self) {
    if (self == NULL) {
        return;
    }

    while (rmlLinkedListGetLength(self) > 0) {
        struct rmlLinkedMapKeyValuePair_ *pair = rmlLinkedListPop(self);
        rmlLinkedMapKeyValuePairDestroy(pair);
    }

    RML_DEBUG("Destroy LinkedMap, also destroy the related LinkedList")
    rmlLinkedListDestroy(self);
}

struct rmlLinkedMapEachEachCallbackAttachment_ {
    rmlLinkedMapEachCallbackContext *mapEachContext;
    rmlLinkedMapEachCallback mapEachCallback;
};

static bool rmlLinkedMapEachEachCallback(rmlLinkedListEachCallbackContext *context) {
    struct rmlLinkedMapEachEachCallbackAttachment_ *attachment = context->attachment;
    if (attachment->mapEachCallback == NULL) {
        // If callback is NULL, break the loop
        return true;
    }

    rmlLinkedMapEachCallbackContext *mapContext = attachment->mapEachContext;
    struct rmlLinkedMapKeyValuePair_ *pair = context->value;
    mapContext->key = pair->key;
    mapContext->value = pair->value;
    return attachment->mapEachCallback(attachment->mapEachContext);
}

void rmlLinkedMapEach(void *self, rmlLinkedMapEachCallback callback, void *attachment) {
    if (self == NULL || callback == NULL) {
        return;
    }

    rmlLinkedMapEachCallbackContext mapEachContext;
    mapEachContext.attachment = attachment;
    mapEachContext.map = self;

    struct rmlLinkedMapEachEachCallbackAttachment_ mapAttachment;
    mapAttachment.mapEachCallback = callback;
    mapAttachment.mapEachContext = &mapEachContext;

    rmlLinkedListEach(self, &rmlLinkedMapEachEachCallback, &mapAttachment);
}