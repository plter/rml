/*
 * RMLFuncContext.h
 *
 *  Created on: Jan 19, 2015
 *      Author: plter
 */

#ifndef RMLFUNCCONTEXT_H_
#define RMLFUNCCONTEXT_H_

#include <iostream>
#include <map>

#include "RMLContext.h"

namespace rml {

class FuncContext: public Context {
public:
	FuncContext(Context * parent);
	virtual ~FuncContext();

	void runText(std::string rmlText);
	void runFile(std::string filePath);

public://override delegate
	virtual void documentStart(Reader * reader);
	virtual void documentEnd(Reader * reader);
	virtual void startElement(Reader * reader,std::string & elementName,std::map<std::string, std::string> & attrs);
	virtual void endElement(Reader * reader,std::string & elementName);
	virtual void foundText(Reader * reader,std::string & text);
	virtual void foundComment(Reader * reader,std::string & comment);
};

} /* namespace rml */

#endif /* RMLFUNCCONTEXT_H_ */
