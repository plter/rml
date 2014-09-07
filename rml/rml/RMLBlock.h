//
//  RMLBlock.h
//  rml
//
//  Created by plter on 9/6/14.
//  Copyright (c) 2014 plter. All rights reserved.
//

#ifndef rml_RMLBlock_h
#define rml_RMLBlock_h

#include "RMLObject.h"
#include <map>
#include <string>

namespace rml {
    class Block:public Object{
        
    public:
        Block(){};
        virtual ~Block(){};
        
    public:
        void addBlock(){
            
        };
        
        std::u16string getName(){
            return _name;
        };
        
        
    private:
        std::u16string _name;
    };
}


#endif
