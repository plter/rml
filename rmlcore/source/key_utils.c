//
// Created by peter on 2022/10/5.
//

#include "../include/key_utils.h"
#include <string.h>

int64_t rml_encode_key(char *key, int64_t prime_number) {
    int64_t length = strlen(key);
    int64_t code1 = 0;
    int64_t code2 = 0;
    for (int i = 0; i < length; ++i) {
        if (i % 2) {
            code1 += key[i];
        } else {
            code2 += key[i];
        }
    }
    int64_t code = (code1 * code2) % prime_number;
    return code;
}