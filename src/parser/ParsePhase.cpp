//
// Created by plter on 6/7/17.
//

#include "ParsePhase.h"

rml::ParsePhase::ParsePhase(rml::ParsePhase &parent) : parent(parent) {

}

rml::ParsePhase &rml::ParsePhase::getParent() const {
    return parent;
}
