//
// Created by plter on 6/7/17.
//

#pragma once

#include "ParsePhase.h"

namespace rml {
    class FuncPhase : public ParsePhase {
    public:
        explicit FuncPhase(ParsePhase &parent);

    };
}
