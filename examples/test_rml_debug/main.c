//
// Created by peter on 2022/10/4.
//

#include <rml_debug_out.h>

int main() {
    RML_DEBUG_OUT(__FILE__, __LINE__, "Hello World %s", "C")

    return 0;
}