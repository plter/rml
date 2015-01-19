/*
 * RMLValue.h
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#ifndef RMLVALUE_H_
#define RMLVALUE_H_

#include "RMLObject.h"
#include "RMLVector.h"
#include <string>
#include <map>
#include <vector>

namespace rml {

class Value: public Object {
public:
	Value(std::string v);
	Value(int32_t v);
	Value(double v);
	Value(float v);
	Value(uint32_t v);
	Value(std::map<std::string,rml::Value*> v);
	Value(rml::Vector<rml::Value*> v);
	virtual ~Value();

public:
	std::string & asString();
	std::map<std::string,rml::Value*> & asTable();
	rml::Vector<rml::Value*> & asArray();
	int32_t asInt32();
	uint32_t asUint32();
	float asNumber32();
	double asNumber64();

	int getType() const {
		return _type;
	}

public:
	static const int TYPE_STRING = 1;
	static const int TYPE_INT32 = 2;
	static const int TYPE_UINT32 = 21;
	static const int TYPE_NUMBER64 = 22;
	static const int TYPE_NUMBER32 = 221;
	static const int TYPE_TABLE = 3;
	static const int TYPE_ARRAY = 4;

private:
	std::string _stringValue;
	std::map<std::string,rml::Value*> _tableValue;
	rml::Vector<rml::Value*> _arrayValue;
	int32_t _int32Value;
	uint32_t _uint32Value;
	float _num32Value;
	double _num64Value;
	int _type;

};

} /* namespace rml */

#endif /* RMLVALUE_H_ */
