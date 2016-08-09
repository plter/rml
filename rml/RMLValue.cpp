/*
 * RMLValue.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#include "RMLValue.h"

namespace rml {


Value::~Value() {
	// TODO Auto-generated destructor stub
}

} /* namespace rml */

rml::Value::Value(std::string v) {
	_type = TYPE_STRING;
	_stringValue = v;
	_int32Value = 0;
	_uint32Value = 0;
	_num32Value = 0;
	_num64Value = 0;
}

rml::Value::Value(int32_t v) {
	_type = TYPE_INT32;
	_int32Value = v;
	_uint32Value = 0;
	_num32Value = 0;
	_num64Value = 0;
}

rml::Value::Value(double v) {
	_type = TYPE_NUMBER64;
	_int32Value = 0;
	_uint32Value = 0;
	_num32Value = 0;
	_num64Value = v;
}

rml::Value::Value(float v) {
	_type = TYPE_NUMBER32;
	_int32Value = 0;
	_uint32Value = 0;
	_num32Value = v;
	_num64Value = 0;
}

rml::Value::Value(uint32_t v) {
	_type = TYPE_UINT32;
	_int32Value = 0;
	_uint32Value = v;
	_num32Value = 0;
	_num64Value = 0;
}

rml::Value::Value(std::map<std::string,rml::Value*> v) {
	_type = TYPE_TABLE;
	_int32Value = 0;
	_uint32Value = 0;
	_num32Value = 0;
	_num64Value = 0;
	_tableValue = v;
}

rml::Value::Value(rml::Vector<rml::Value*> v) {
	_type = TYPE_ARRAY;
	_int32Value = 0;
	_uint32Value = 0;
	_num32Value = 0;
	_num64Value = 0;
	_arrayValue = v;
}

std::string& rml::Value::asString() {
	return _stringValue;
}

std::map<std::string,rml::Value*>& rml::Value::asTable() {
	return _tableValue;
}

rml::Vector<rml::Value*>& rml::Value::asArray() {
	return _arrayValue;
}

int32_t rml::Value::asInt32() {
	return _int32Value;
}

uint32_t rml::Value::asUint32() {
	return _uint32Value;
}

float rml::Value::asNumber32() {
	return _num32Value;
}

double rml::Value::asNumber64() {
	return _num64Value;
}
