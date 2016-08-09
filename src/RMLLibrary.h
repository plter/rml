/*
 * RMLLibrary.h
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#ifndef RMLLIBRARY_H_
#define RMLLIBRARY_H_

#include "RMLObject.h"
#include "RMLFunc.h"
#include <iostream>
#include <map>
#include <string>

namespace rml {

class Library: public Object {

private:
	Library();

public:
	void addFunc(rml::Func * func);
	void removeFunc(rml::Func * func);
	Func * getFunc(std::string & name);
	static Library * getInstance();

public:
	virtual ~Library();

private:
	void addSystemFuncs();

private:
	std::map<std::string,Func*> _funcsMap;
};

} /* namespace src */

#endif /* RMLLIBRARY_H_ */
