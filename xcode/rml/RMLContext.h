/*
 * RMLContext.h
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#ifndef RMLCONTEXT_H_
#define RMLCONTEXT_H_

#include <string>

#include "RMLCall.h"
#include "RMLObject.h"
#include "RMLReader.h"
#include "RMLIReaderDelegate.h"

namespace rml{

class Context:public rml::Object,public rml::IReaderDelegate{

private:
	rml::Call * _currentCall;
	bool _inArg;

public:
	Context();
	virtual ~Context();

public:
	void runText(std::string rmlText);
	void runFile(std::string filePath);

public://implement IReaderDelegate
	virtual void documentStart();
	virtual void documentEnd();
	virtual void startElement(std::string & elementName,std::map<std::string, std::string> & attrs);
	virtual void endElement(std::string & elementName);
	virtual void foundText(std::string & text);
	virtual void foundComment(std::string & comment);
};

} /* namespace rml */

#endif /* RMLCONTEXT_H_ */
