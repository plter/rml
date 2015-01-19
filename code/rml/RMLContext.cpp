/*
 * RMLContext.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#include <fstream>
#include <sstream>
#include "RMLContext.h"
#include "RMLKeyWords.h"
#include "RMLCall.h"

namespace rml {
    
    rml::Call * _currentCall = NULL;
    
    Context::Context(Context * parent) {
        _currentCall = NULL;
        _inArg = false;
        _parent = parent;
        
        if (_parent) {
            _parent->retain();
        }
    }
    
    Context::~Context() {
        if (_parent) {
            _parent->release();
        }
    }
    
    void Context::runText(std::string rmlText) {
        
        rml::Reader r(rmlText,this);
        r.read();
    }
    
    void Context::runFile(std::string filePath) {
        std::ifstream f(filePath);
        std::stringbuf sb;
        f >> &sb;
        f.close();
        
        runText(sb.str());
    }
    
    void Context::documentStart(Reader *reader) {
    }
    
    void Context::documentEnd(Reader *reader) {
    }
    
    void Context::startElement(Reader *reader,std::string& elementName,std::map<std::string, std::string>& attrs) {
        if (elementName.compare(RML_KEY_WORD_CALL)==0) {
            std::string name = attrs["name"];
            _currentCall = new Call(this,name);
        }else if(elementName.compare(RML_KEY_WORD_ARG)==0){
            _inArg = true;
        }
    }
    
    void Context::endElement(Reader *reader,std::string& elementName) {
        if (elementName.compare(RML_KEY_WORD_CALL)==0) {
            _currentCall->exec();
            _currentCall->release();
            _currentCall = NULL;
        }else if(elementName.compare(RML_KEY_WORD_ARG)==0){
            _inArg = false;
        }
    }
    
    void Context::foundText(Reader *reader,std::string& text) {
        if (_inArg) {
            Value * v = new Value(text);
            _currentCall->pushArg(v);
            v->release();
        }
    }
    
    void Context::foundComment(Reader *reader,std::string& comment) {
    }
    
} /* namespace rml */
