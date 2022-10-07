//
// Created by peter on 2022/10/6.
//

#ifndef RML_RMLMAP_H
#define RML_RMLMAP_H

void *rmlMapCreate();

void rmlMapPut(void *self, char *key, void *value);

void *rmlMapRemove(void *self, char *key);

void *rmlMapGet(void *self, char *key);

void rmlMapDestroy(void *self);

#endif //RML_RMLMAP_H
