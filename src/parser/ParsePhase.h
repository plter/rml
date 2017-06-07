//
// Created by plter on 6/7/17.
//

#pragma once

#include "IReaderDelegate.h"

namespace rml {

    /**
     * 解析过程可以分成很多阶段，在子阶段完成后应该转交回父阶段继续解析
     */
    class ParsePhase : IReaderDelegate {

    public:
        ParsePhase(ParsePhase &parent);

        ParsePhase &getParent() const;

    private:
        ParsePhase &parent;
    };
}

