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
	Context * _parent;

public:
	Context(Context * parent);
	virtual ~Context();

public:
	inline Context * getParentContext(){
		return _parent;
	};
};

} /* namespace rml */

#endif /* RMLCONTEXT_H_ */
