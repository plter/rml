//
//  RMLFunc.h
//  rml
//
//  Created by plter on 9/6/14.
//  Copyright (c) 2014 plter. All rights reserved.
//

#pragma once

#include "RMLObject.h"
#include <map>
#include <string>

namespace rml {
    class Func:public Object{
        
    public:
        Func();
        virtual ~Func();
        
    public:
        void addFunc();
        
        inline std::string getName(){
            return _name;
        };
        
        
    private:
        std::string _name;
    };
}

