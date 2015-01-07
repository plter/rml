//
//  RMLReader.h
//  rml
//
//  Created by plter on 9/5/14.
//  Copyright (c) 2014 plter. All rights reserved.
//

#ifndef rml_RMLReader_h
#define rml_RMLReader_h

#include <iostream>
#include <string>
#include "RMLIReaderDelegate.h"
#include <map>
#include "RMLObject.h"

namespace rml {
    
    class Reader:public Object{
        
    private:
        std::string _rmlContent;
        IReaderDelegate * _delegate;
        
    public:
        /********************************
         Construct a RMLReader object
         @param rmlContent  The rml file content
         @param delegate    The delegate to parse rml file
         ********************************/
        Reader(std::string & rmlContent,IReaderDelegate * delegate){
            _rmlContent = rmlContent;
            _delegate = delegate;
            
            dynamic_cast<Object*>(_delegate)->retain();
        };
        
        void read();
        
        virtual ~ Reader(){
            dynamic_cast<Object*>(_delegate)->release();
        };
    };
}

#endif
