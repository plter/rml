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
#include "RMLReaderDelegate.h"
#include <map>
#include "RMLTool.h"

namespace rml {
    
    class RMLReader{
        
    private:
        std::u16string _rmlContent;
        RMLReaderDelegate * _delegate;
        
    public:
        /********************************
         Construct a RMLReader object
         @param rmlContent  The rml file content
         @param delegate    The delegate to parse rml file
         ********************************/
        RMLReader(std::u16string & rmlContent,RMLReaderDelegate & delegate){
            _rmlContent = rmlContent;
            _delegate = &delegate;
        };
        
        void parse(){
            
            long size = _rmlContent.size();
            
            _delegate->documentStart();
            int inCount = 0;
            std::u16string currentStr;
            char16_t currentC;
            int contentTextBegin = 0;//init content begin index
            
            for (int i=0; i<size; ++i) {
                
                if (_rmlContent[i]=='<') {
                    currentStr = u"";
                    for (int j = i+1; j<size&&(currentC=_rmlContent[j])!='>'; ++j) {
                        currentStr+=currentC;
                    }
                    i +=currentStr.size()+1;
                    long currentStrSize = currentStr.size();
                    
                    currentC = currentStr[0];
                    if (currentC=='/') {//end element
                        std::u16string endElementName = currentStr.substr(1,currentStr.size()-1);
                        _delegate->endElement(endElementName);
                        
                        if (contentTextBegin) {
                            //found a text content. @mark(readTextContent) content text end
                            std::u16string textContent = _rmlContent.substr(contentTextBegin,i-contentTextBegin-currentStrSize-1);
                            
                            if (!textContent.empty()) {
                                _delegate->foundText(textContent);
                            }
                            
                            contentTextBegin = 0;
                        }
                        
                        inCount--;
                        if (inCount<=0) {
                            _delegate->documentEnd();
                            
                            return;//break all loop
                        }
                    }else if (currentC=='!'){//the currentStr is a comment
                        std::u16string comment = currentStr.substr(1,currentStr.size()-1);
                        _delegate->foundComment(comment);
                    }else{//start element
                        inCount++;
                        
                        //Set current content text begin index. @mark(readTextContent) content text begin
                        contentTextBegin = i+1;
                        
                        std::map<std::u16string,std::u16string> attrs;
                        std::u16string elementName;
                        
                        int k = 0;
                        //read element name
                        for (; k<currentStrSize&&(currentC=currentStr[k])!=' '; ++k) {
                            elementName+=currentC;
                        }
                        
                        //read kvs
                        for (; k<currentStrSize; ++k) {
                            
                            if (currentStr[k]=='=') {
                                std::u16string key,value;
                                
                                //find key
                                for (int a = k-1; a>0; --a) {
                                    currentC = currentStr[a];
                                    
                                    if (currentC!=' ') {
                                        for (int b=a; b>0&&(currentC=currentStr[b])!=' '; --b) {
                                            key+=currentC;
                                        }
                                        
                                        std::u16string tmp = key;
                                        key.assign(tmp.rbegin(), tmp.rend());
                                        break;
                                    }
                                }
                                
                                //find value
                                for (int c = k; c<currentStrSize; ++c) {
                                    currentC = currentStr[c];
                                    
                                    if (currentC=='"') {
                                        for (int d = c+1;
                                             d<currentStrSize&&(currentC=currentStr[d])!='"';
                                             ++d) {
                                            value+=currentC;
                                            
                                            k = d;
                                        }
                                        
                                        break;
                                    }
                                }
                                
                                attrs[key] = value;
                            }
                        }
                        
                        _delegate->startElement(elementName, attrs);
                    }
                }
            }
        };
        
        virtual ~ RMLReader(){
            
        };
    };
}

#endif
