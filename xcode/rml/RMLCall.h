/*
 * RMLCall.h
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#ifndef RMLCALL_H_
#define RMLCALL_H_

#include "RMLObject.h"
#include <string>
#include "RMLVector.h"
#include "RMLValue.h"

namespace rml {

class Call :public rml::Object{

public:
	Call(std::string name);
	virtual ~Call();

public:
	void pushArg(rml::Value * arg);
	void exec();
	rml::Value * at(uint32_t index);

	const std::string& getName() const {
		return _name;
	}

private:
	std::string _name;
	rml::Vector<rml::Value*> _args;
};

} /* namespace rml */

#endif /* RMLCALL_H_ */
