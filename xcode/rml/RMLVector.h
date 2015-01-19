/*
 * RMLVector.h
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#ifndef RMLVECTOR_H_
#define RMLVECTOR_H_

#include "RMLObject.h"
#include <vector>

namespace rml {

template<class T>
class Vector: public Object {
public:
	Vector(){};
	virtual ~Vector(){
		clear();
	};

public:
	void push(T v){
		_vect.push_back(v);
		v->retain();
	};

	void pop(){
		auto back = _vect.back();
		_vect.pop_back();
		back->release();
	}

	T at(uint32_t index){
		return _vect[index];
	}

	void clear(){
		if(_vect.size()){
			pop();
		}
	}

private:
	std::vector<T> _vect;
};

} /* namespace rml */

#endif /* RMLVECTOR_H_ */
