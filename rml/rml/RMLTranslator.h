//
//  RMLTranslator.h
//  rml
//
//  Created by plter on 9/6/14.
//  Copyright (c) 2014 plter. All rights reserved.
//

#ifndef rml_RMLTranslator_h
#define rml_RMLTranslator_h

#include <string>
#include "RMLReader.h"

namespace rml {
    class Translator:Object{
        
    public:
        Translator(std::u16string & rmlContent){
            _reader = new Reader(rmlContent,this);
            
        };
        virtual ~Translator(){
            _reader->release();
        };
        
    public:
        static Translator * getInstance(){
            static Translator * __ins = NULL;
            
            if (!__ins) {
                __ins = new Translator();
            }
            
            return __ins;
        };
        
    private:
        Reader * _reader;
    };
}

#endif
