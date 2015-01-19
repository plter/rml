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

namespace rml {

Context::Context() {
	_currentCall = NULL;
	_inArg = false;
}

Context::~Context() {
	// TODO Auto-generated destructor stub
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

void Context::documentStart() {
}

void Context::documentEnd() {
}

void Context::startElement(std::string& elementName,std::map<std::string, std::string>& attrs) {
	if (elementName.compare(RML_KEY_WORD_CALL)==0) {
		std::string name = attrs["name"];
		_currentCall = new Call(name);
	}else if(elementName.compare(RML_KEY_WORD_ARG)==0){
		_inArg = true;
	}
}

void Context::endElement(std::string& elementName) {
	if (elementName.compare(RML_KEY_WORD_CALL)==0) {
		_currentCall->exec();
		_currentCall->release();
		_currentCall = NULL;
	}else if(elementName.compare(RML_KEY_WORD_ARG)==0){
		_inArg = false;
	}
}

void Context::foundText(std::string& text) {
	if (_inArg) {
		auto v = new Value(text);
		_currentCall->pushArg(v);
		v->release();
	}
}

void Context::foundComment(std::string& comment) {
}

} /* namespace rml */
