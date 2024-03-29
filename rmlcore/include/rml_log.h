//
// Created by peter on 2022/10/4.
//

#pragma once

#define RML_LOG_LEVEL_VERBOSE 1
#define RML_LOG_LEVEL_DEBUG 2
#define RML_LOG_LEVEL_INFO 3
#define RML_LOG_LEVEL_WARN 4
#define RML_LOG_LEVEL_ERROR 5

#ifndef RML_LOG_LEVEL
#define RML_LOG_LEVEL RML_LOG_LEVEL_INFO
#endif

#include <stdio.h>
#include "time_utils.h"

#define RML_OUTPUT(LEVEL, FORMAT, ARGS...) {                        \
    char timebuf[32];                                               \
    rml_get_current_local_time(timebuf,32);                         \
    printf("[%s] %s(%d) [%s] ",timebuf,__FILE__,__LINE__,LEVEL);    \
    printf(FORMAT,##ARGS);                                          \
    printf("\n");                                                   \
}

#define RML_LOG_VERBOSE_ENABLED RML_LOG_LEVEL<=RML_LOG_LEVEL_VERBOSE
#define RML_LOG_DEBUG_ENABLED RML_LOG_LEVEL<=RML_LOG_LEVEL_DEBUG
#define RML_LOG_INFO_ENABLED RML_LOG_LEVEL<=RML_LOG_LEVEL_INFO
#define RML_LOG_WARN_ENABLED RML_LOG_LEVEL<=RML_LOG_LEVEL_WARN
#define RML_LOG_ERROR_ENABLED RML_LOG_LEVEL<=RML_LOG_LEVEL_ERROR

#define RML_DEBUG(FORMAT, ARGS...)          \
    if(RML_LOG_DEBUG_ENABLED){ \
        RML_OUTPUT("DEBUG",FORMAT,##ARGS)   \
    }

#define RML_VERBOSE(FORMAT, ARGS...)          \
    if(RML_LOG_VERBOSE_ENABLED){ \
        RML_OUTPUT("VERBOSE",FORMAT,##ARGS)   \
    }

#define RML_INFO(FORMAT, ARGS...)           \
    if(RML_LOG_INFO_ENABLED){  \
        RML_OUTPUT("INFO",FORMAT,##ARGS)    \
    }


#define RML_WARN(FORMAT, ARGS...)          \
    if(RML_LOG_WARN_ENABLED){ \
        RML_OUTPUT("WARN",FORMAT,##ARGS)   \
    }

#define RML_ERROR(FORMAT, ARGS...)          \
    if(RML_LOG_ERROR_ENABLED){ \
        RML_OUTPUT("ERROR",FORMAT,##ARGS)   \
    }


