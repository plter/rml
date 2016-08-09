//
// Created by plter on 8/8/16.
//

#include "Context.h"

namespace rml {


    Context::Context(Context *parent) {
        _parent = parent;
    }

    Context::~Context() {

    }
}