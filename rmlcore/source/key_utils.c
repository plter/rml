//
// Created by peter on 2022/10/5.
//

#include "../include/key_utils.h"
#include <string.h>

int64_t rml_encode_key(char *key, int64_t prime_number) {
    int64_t length = strlen(key);
    int64_t code1 = 1;
    int64_t code2 = 1;
    int64_t code3 = 1;
    int64_t code4 = 1;
    uint8_t current = 0;
    for (int i = 0; i < length; ++i) {
        current = key[i];
        code1 += current;
        if (i % 2 == 0) {
            code2 += current;
        }
        if (i % 3 == 0) {
            code3 += current;
        }
        if (i % 4 == 0) {
            code4 += current;
        }
    }
    int64_t code = (code1 * code2 * code3 * code4) % prime_number;
    return code;
}