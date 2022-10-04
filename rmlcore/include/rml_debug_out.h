//
// Created by peter on 2022/10/4.
//

#ifndef RML_RML_DEBUG_OUT_H
#define RML_RML_DEBUG_OUT_H

#ifndef RML_DEBUG
#define RML_DEBUG 0
#endif

#include <stdio.h>

#define RML_DEBUG_OUT(FILE, LINE, FORMAT, ARGS...)  \
    if(RML_DEBUG){                                  \
        printf("%s(%d) ",FILE,LINE);                \
        printf(FORMAT,##ARGS);                      \
        printf("\n");                               \
    }

#endif //RML_RML_DEBUG_OUT_H
