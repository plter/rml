//
// Created by peter on 2022/10/5.
//

#include "../include/time_utils.h"
#include <time.h>

void rml_get_current_local_time(char *buf, int buf_length) {
    time_t t;
    time(&t);
    struct tm *tinfo = localtime(&t);
    strftime(buf, buf_length, "%Y-%m-%d %H:%M:%S", tinfo);
}