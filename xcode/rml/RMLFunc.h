/*
 * RMLFunc.h
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#ifndef RMLFUNC_H_
#define RMLFUNC_H_

#include "RMLObject.h"
#include "RMLCall.h"
#include <string>

namespace rml {

class Func: public Object {
public:
	Func(std::string name);
	virtual ~Func();

	virtual void exec(rml::Call * call)=0;

	const std::string& getName() const {
		return _name;
	}

private:
	std::string _name;
};

} /* namespace rml */

#endif /* RMLFUNC_H_ */
