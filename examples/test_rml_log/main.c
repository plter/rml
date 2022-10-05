//
// Created by peter on 2022/10/4.
//

#include <rml_debug_out.h>

int main() {
    RML_DEBUG("Hello World %d", 100)
    RML_INFO("Message 2")
    RML_WARN("Message 3")
    RML_ERROR("Message 4")
    return 0;
}