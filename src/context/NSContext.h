//
// Created by plter on 8/9/16.
//

#pragma once

#include "Context.h"

namespace rml {

    class NSContext :public Context{
    public:
        NSContext(Context *parent);

    };
}
