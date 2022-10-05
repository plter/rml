//
// Created by peter on 2022/10/5.
//

#include <time_utils.h>
#include <stdio.h>

int main() {
    char buf[32];
    get_current_local_time(buf, 32);
    printf("%s\n", buf);
    return 0;
}