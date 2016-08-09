/*
 * RMLCall.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#include <iostream>

#include "RMLCall.h"
#include "RMLLibrary.h"
#include "RMLKeyWords.h"


namespace rml {

    Call::Call(Context *parent, std::string name) : Context(parent) {
        _name = name;
        _currentArgContext = NULL;
    }

    Call::~Call() {
        // TODO Auto-generated destructor stub
    }

    void Call::exec() {
        auto func = rml::Library::getInstance()->getFunc(_name);
        if (func) {
            func->exec(this);
        } else {
            std::cout << "Can not find function named " << _name << std::endl;
        }
    }

    rml::Value *Call::at(uint32_t index) {
        return _args.at(index);
    }

} /* namespace rml */

void rml::Call::pushArg(rml::Value *arg) {
    _args.push(arg);
}

void rml::Call::documentStart(Reader *reader) {
}

void rml::Call::documentEnd(Reader *reader) {
}

void rml::Call::startElement(Reader *reader, std::string &elementName,
                             std::map<std::string, std::string> &attrs) {
    if (elementName.compare(RML_KEY_WORD_ARG) == 0) {
        _currentArgContext = new rml::ArgContext(this);
        reader->setDelegate(_currentArgContext);
    }
}

void rml::Call::endElement(Reader *reader, std::string &elementName) {
    if (elementName.compare(RML_KEY_WORD_ARG) == 0) {
        pushArg(_currentArgContext->getValue());
        _currentArgContext->release();
        _currentArgContext = NULL;
    } else if (elementName.compare(RML_KEY_WORD_CALL) == 0) {
        getParentContext()->endElement(reader, elementName);
        reader->setDelegate(getParentContext());
    }
}

void rml::Call::foundText(Reader *reader, std::string &text) {
}

void rml::Call::foundComment(Reader *reader, std::string &comment) {
}
