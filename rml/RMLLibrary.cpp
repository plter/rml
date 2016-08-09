/*
 * RMLLibrary.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#include "RMLLibrary.h"
#include "funcs/PrintFunc.h"

namespace rml {



Library::Library() {
	// TODO Auto-generated constructor stub
	addSystemFuncs();
}

Library::~Library() {
	// TODO Auto-generated destructor stub
}

void Library::addFunc(rml::Func* func) {
	func->retain();
	_funcsMap[func->getName()] = func;
}

void Library::removeFunc(rml::Func* func) {
	_funcsMap.erase(func->getName());
	func->release();
}

Library* Library::getInstance() {
	static Library * __ins = NULL;
	if (!__ins) {
		__ins = new Library();
	}
	return __ins;
}

void Library::addSystemFuncs() {
	//add print func
	rml::funcs::PrintFunc * f = new rml::funcs::PrintFunc();
	addFunc(f);
}

Func* Library::getFunc(std::string & name) {
	return _funcsMap[name];
}

} /* namespace rml */

