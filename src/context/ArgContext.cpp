/*
 * RMLArgContext.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: plter
 */

#include "ArgContext.h"
#include "RMLKeyWords.h"

namespace rml {

    ArgContext::ArgContext(Context *parent) : Context(parent) {
        _value = NULL;
    }

    ArgContext::~ArgContext() {
        if (_value) {
            _value->release();
        }
    }

    void ArgContext::documentStart(Reader *reader) {
    }

    void ArgContext::documentEnd(Reader *reader) {
    }

    void ArgContext::startElement(Reader *reader, std::string &elementName,
                                  std::map<std::string, std::string> &attrs) {
    }

    void ArgContext::endElement(Reader *reader, std::string &elementName) {
        if (elementName.compare(RML_KEY_WORD_ARG) == 0) {
            getParentContext()->endElement(reader, elementName);
            reader->setDelegate(getParentContext());
        }
    }

    void ArgContext::foundText(Reader *reader, std::string &text) {
        _value = new Value(text);
    }

    void ArgContext::foundComment(Reader *reader, std::string &comment) {
    }

} /* namespace src */
