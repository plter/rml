//
// Created by peter on 2022/10/5.
//

#include <stdio.h>
#include <key_utils.h>


int main() {
    printf("code: %lld\n", rml_encode_key("hello", 101));
    printf("code: %lld\n", rml_encode_key("elllo", 101));
    printf("code: %lld\n", rml_encode_key("hello1", 101));
    return 0;
}