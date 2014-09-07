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
#include "RMLObject.h"
#include "RMLIReaderDelegate.h"
#include "RMLBlock.h"

namespace rml {
    class Translator:public Object,IReaderDelegate{
        
    public:
        Translator(){
            _currentReader = NULL;
            _currentBlock = NULL;
            _rootBlock = NULL;
        };
        
        Block * translate(std::u16string & rmlContent){
            if (_currentReader) {
                _currentReader->release();
            }
            _currentReader = new Reader(rmlContent,this);
            
            if (_currentBlock) {
                _currentBlock->release();
            }
            _currentReader->read();
            return _rootBlock;
        };
        
        virtual void documentStart(){
            //TODO
        };
        virtual void documentEnd(){
            //TODO
        };
        virtual void startElement(std::u16string & elementName,std::map<std::u16string, std::u16string> & attrs){
            //TODO
        };
        virtual void endElement(std::u16string & elementName){
            //TODO
        };
        virtual void foundText(std::u16string & text){
            //TODO
        };
        virtual void foundComment(std::u16string & comment){
            //TODO
        };
        
        
        virtual ~Translator(){
            _currentReader->release();
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
        Reader * _currentReader;
        Block * _currentBlock,*_rootBlock;
    };
}

#endif
