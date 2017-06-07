//
// Created by plter on 6/7/17.
//

#include "MiddleCode.h"

rml::mc::MiddleCode::MiddleCode(const std::string &name) : name(name) {}

const std::string &rml::mc::MiddleCode::getName() const {
    return name;
}
