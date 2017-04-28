/*
 * PrintFunc.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#include "PrintFunc.h"

#include <iostream>

namespace rml {
namespace funcs {

PrintFunc::PrintFunc():Func("print") {
	// TODO Auto-generated constructor stub

}

PrintFunc::~PrintFunc() {
	// TODO Auto-generated destructor stub
}

void PrintFunc::exec(rml::Call* call) {
	std::cout<<call->at(0)->asString()<<"\n";
}

} /* namespace funcs */
} /* namespace src */
