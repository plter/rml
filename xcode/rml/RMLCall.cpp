/*
 * RMLCall.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#include <iostream>

#include "RMLCall.h"
#include "RMLLibrary.h"
#include "RMLFunc.h"

namespace rml {

Call::Call(std::string name) {
	_name = name;
}

Call::~Call() {
	// TODO Auto-generated destructor stub
}

void Call::exec() {
	rml::Library::getInstance()->getFunc(_name)->exec(this);
}

rml::Value* Call::at(uint32_t index) {
	return _args.at(index);
}

} /* namespace rml */

void rml::Call::pushArg(rml::Value* arg) {
	_args.push(arg);
}
