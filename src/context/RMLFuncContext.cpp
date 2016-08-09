/*
 * RMLFuncContext.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: plter
 */

#include "RMLFuncContext.h"

#include <fstream>
#include <sstream>

#include "RMLCall.h"
#include "RMLKeyWords.h"

namespace rml {

    rml::Call *_currentCall = NULL;

    FuncContext::FuncContext(Context *parent) : Context(parent) {
        _currentCall = NULL;
    }

    FuncContext::~FuncContext() {
        // TODO Auto-generated destructor stub
    }


    void FuncContext::runText(std::string rmlText) {

        rml::Reader r(rmlText, this);
        r.read();
    }

    void FuncContext::runFile(std::string filePath) {
        std::ifstream f(filePath);
        std::stringbuf sb;
        f >> &sb;
        f.close();

        runText(sb.str());
    }

    void FuncContext::documentStart(Reader *reader) {
    }

    void FuncContext::documentEnd(Reader *reader) {
    }

    void
    FuncContext::startElement(Reader *reader, std::string &elementName, std::map<std::string, std::string> &attrs) {
        if (elementName.compare(RML_KEY_WORD_CALL) == 0) {
            std::string name = attrs["name"];
            _currentCall = new Call(this, name);
            reader->setDelegate(_currentCall);
        }
    }

    void FuncContext::endElement(Reader *reader, std::string &elementName) {
        if (elementName.compare(RML_KEY_WORD_CALL) == 0) {
            _currentCall->exec();
            _currentCall->release();
            _currentCall = NULL;
        }
    }

    void FuncContext::foundText(Reader *reader, std::string &text) {
    }

    void FuncContext::foundComment(Reader *reader, std::string &comment) {
    }

} /* namespace src */
