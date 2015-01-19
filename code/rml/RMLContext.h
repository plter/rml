/*
 * RMLContext.h
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#ifndef RMLCONTEXT_H_
#define RMLCONTEXT_H_

#include <string>

#include "RMLObject.h"
#include "RMLReader.h"
#include "RMLIReaderDelegate.h"


namespace rml{

class Context:public rml::Object,public rml::IReaderDelegate{

private:
	bool _inArg;
    Context * _parent;

public:
	Context(Context * parent);
	virtual ~Context();

public:
	void runText(std::string rmlText);
	void runFile(std::string filePath);
    inline Context * getParentContext(){
        return _parent;
    };

public://implement IReaderDelegate
	virtual void documentStart(Reader *reader);
	virtual void documentEnd(Reader *reader);
	virtual void startElement(Reader *reader,std::string & elementName,std::map<std::string, std::string> & attrs);
	virtual void endElement(Reader *reader,std::string & elementName);
	virtual void foundText(Reader *reader,std::string & text);
	virtual void foundComment(Reader *reader,std::string & comment);
};

} /* namespace rml */

#endif /* RMLCONTEXT_H_ */
