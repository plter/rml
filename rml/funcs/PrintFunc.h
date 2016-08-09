/*
 * PrintFunc.h
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#ifndef FUNCS_PRINTFUNC_H_
#define FUNCS_PRINTFUNC_H_

#include "../RMLFunc.h"

namespace rml {
namespace funcs {

class PrintFunc: public rml::Func {
public:
	PrintFunc();
	virtual ~PrintFunc();

public:
	virtual void exec(rml::Call * call);
};

} /* namespace funcs */
} /* namespace rml */

#endif /* FUNCS_PRINTFUNC_H_ */
