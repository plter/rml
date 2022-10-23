//
// Created by peter on 2022/10/6.
//


#include "../include/rmlMap.h"
#include "../include/rmlLinkedMap.h"
#include "../include/rml_log.h"
#include "../include/key_utils.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int64_t rmlPrimeNumberList[] = rml_PRIME_NUMBERS;

struct rmlMap_ {
    void **linearSpace_;
    int64_t currentPrimeNumberIndex_;
    int64_t currentLinearSpaceSize_;
    int64_t length_;
};

static void rmlMapReset(struct rmlMap_ *self) {
    self->linearSpace_ = NULL;
    self->currentPrimeNumberIndex_ = 0;
    self->length_ = 0;
    self->currentLinearSpaceSize_ = rmlPrimeNumberList[self->currentPrimeNumberIndex_];
}

static void **rmlMapLinearSpaceCreate_(struct rmlMap_ *map) {
    RML_VERBOSE("Create Map Linear Space")
    int64_t memSize = sizeof(void *) * map->currentLinearSpaceSize_;
    void **space = malloc(memSize);
    for (int i = 0; i < map->currentLinearSpaceSize_; ++i) {
        space[i] = NULL;
    }
    return space;
}

static void rmlMapLinearSpaceDestroy(void **space) {
    RML_VERBOSE("Destroy Map Linear Space")
    free(space);
}

void *rmlMapCreate() {
    RML_VERBOSE("Create Map");
    struct rmlMap_ *map = malloc(sizeof(struct rmlMap_));
    rmlMapReset(map);
    map->linearSpace_ = rmlMapLinearSpaceCreate_(map);
    return map;
}

struct rmlMapRehashEachCallbackAttachment {
    struct rmlMap_ *map;
};


/**
 * Just put key-value to the map, do not do any change to the map it self
 *
 * @param self
 * @param key
 * @param value
 * @return
 */
static void *rmlMapJustPut_(void *self, char *key, void *value) {
    struct rmlMap_ *theMap = self;
    int64_t index = rml_encode_key(key, theMap->currentLinearSpaceSize_);
    void *linkedMap = theMap->linearSpace_[index];
    if (linkedMap == NULL) {
        linkedMap = rmlLinkedMapCreate();
        theMap->linearSpace_[index] = linkedMap;
    }
    int64_t linkedMapOldLength = rmlLinkedMapGetLength(linkedMap);
    rmlLinkedMapPut(linkedMap, key, value);
    int64_t linkedMapNewLength = rmlLinkedMapGetLength(linkedMap);
    theMap->length_ += linkedMapNewLength - linkedMapOldLength;
    return value;
}

static bool rmlMapRehashEachCallback(rmlLinkedMapEachCallbackContext *context) {
    struct rmlMapRehashEachCallbackAttachment *attachment = context->attachment;
    rmlMapJustPut_(attachment->map, context->key, context->value);
    return false;
}

void *rmlMapPut(void *self, char *key, void *value) {
    struct rmlMap_ *theMap = self;

    if (rmlMapGetLength(theMap) > theMap->currentLinearSpaceSize_ * 3 / 5) {
        if (theMap->currentPrimeNumberIndex_ < rml_PRIME_NUMBERS_COUNT - 1) {
            // Store old properties
            void **oldSpace = theMap->linearSpace_;
            int64_t oldPrimeNumber = theMap->currentLinearSpaceSize_;

            theMap->currentPrimeNumberIndex_++;
            theMap->currentLinearSpaceSize_ = rmlPrimeNumberList[theMap->currentPrimeNumberIndex_];
            // Rehash the linear space
            theMap->linearSpace_ = rmlMapLinearSpaceCreate_(theMap);
            theMap->length_ = 0;
            struct rmlMapRehashEachCallbackAttachment attachment;
            for (int i = 0; i < oldPrimeNumber; ++i) {
                void *linkedMap = oldSpace[i];
                if (linkedMap != NULL) {
                    attachment.map = theMap;
                    rmlLinkedMapEach(linkedMap, &rmlMapRehashEachCallback, &attachment);
                }
            }

            rmlMapLinearSpaceDestroy(oldSpace);
        }
    }

    return rmlMapJustPut_(self, key, value);
}

void *rmlMapRemove(void *self, char *key) {
    assert(key != NULL);
    struct rmlMap_ *theMap = self;
    int64_t index = rml_encode_key(key, theMap->currentLinearSpaceSize_);
    void *linkedMap = theMap->linearSpace_[index];
    if (linkedMap == NULL) {
        return NULL;
    }

    void *value = rmlLinkedMapRemove(linkedMap, key);
    if (value != NULL) {
        theMap->length_--;
    }
    if (rmlLinkedMapGetLength(linkedMap) <= 0) {
        rmlLinkedMapDestroy(linkedMap);
        theMap->linearSpace_[index] = NULL;
    }
    return value;
}

void *rmlMapGet(void *self, char *key) {
    assert(key != NULL);
    struct rmlMap_ *theMap = self;

    int64_t index = rml_encode_key(key, theMap->currentLinearSpaceSize_);
    void *linkedMap = theMap->linearSpace_[index];
    if (linkedMap == NULL) {
        return NULL;
    }

    return rmlLinkedMapGet(linkedMap, key);
}

int64_t rmlMapGetLength(void *self) {
    return ((struct rmlMap_ *) self)->length_;
}

int64_t rmlMapGetLinearSpaceSize(void *self) {
    return ((struct rmlMap_ *) self)->currentLinearSpaceSize_;
}

void rmlMapDestroy(void *self) {
    struct rmlMap_ *theMap = self;
    for (int i = 0; i < theMap->currentLinearSpaceSize_; ++i) {
        rmlLinkedMapDestroy(theMap->linearSpace_[i]);
    }
    rmlMapLinearSpaceDestroy(theMap->linearSpace_);
    free(theMap);
    RML_VERBOSE("Destroy Map")
}