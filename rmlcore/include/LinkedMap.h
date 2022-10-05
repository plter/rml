//
// Created by peter on 2022/10/4.
//

#ifndef RML_LINKEDMAP_H
#define RML_LINKEDMAP_H

void *LinkedMapCreate();

void LinkedMapDestroy(void *self);

void LinkedMapPut(char *key, void *value);

#endif //RML_LINKEDMAP_H
