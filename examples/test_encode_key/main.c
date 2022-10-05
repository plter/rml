//
// Created by peter on 2022/10/5.
//

#include <stdio.h>
#include <key_utils.h>


int main() {
    int64_t prime_number = 29;
    printf("code: %lld\n", rml_encode_key("hello", prime_number));
    printf("code: %lld\n", rml_encode_key("elllo", prime_number));
    printf("code: %lld\n", rml_encode_key("hello1", prime_number));
    printf("code: %lld\n", rml_encode_key("汉字", prime_number));
    printf("code: %lld\n", rml_encode_key("字汉", prime_number));
    printf("code: %lld\n", rml_encode_key("汉字字符", prime_number));
    printf("code: %lld\n", rml_encode_key("字符汉字", prime_number));
    printf("code: %lld\n", rml_encode_key("日本語", prime_number));
    printf("code: %lld\n", rml_encode_key("日語本", prime_number));
    printf("code: %lld\n", rml_encode_key("한국", prime_number));
    return 0;
}