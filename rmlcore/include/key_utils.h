//
// Created by peter on 2022/10/5.
//

#ifndef RML_KEY_UTILS_H
#define RML_KEY_UTILS_H

#include <stdint.h>

#define rml_PRIME_NUMBERS_COUNT 10
#define rml_PRIME_NUMBERS {101,211,401,797,1601,3203,6421,12809,25601,49999};

int64_t rml_encode_key(char *key, int64_t prime_number);

#endif //RML_KEY_UTILS_H
