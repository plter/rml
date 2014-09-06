//
//  RMLReaderDelegate.h
//  rml
//
//  Created by plter on 9/5/14.
//  Copyright (c) 2014 plter. All rights reserved.
//

#ifndef rml_RMLReaderDelegate_h
#define rml_RMLReaderDelegate_h

#include <map>

namespace rml {
    class RMLReaderDelegate{
        
    public:
        virtual void documentStart(){};
        virtual void documentEnd(){};
        virtual void startElement(std::u16string elementName,std::map<std::u16string, std::u16string> attrs){};
        virtual void endElement(std::u16string elementName){};
        virtual void foundText(std::u16string text){};
        virtual void foundComment(std::u16string comment){};
    };
}

#endif
