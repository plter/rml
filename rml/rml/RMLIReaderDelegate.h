//
//  RMLReaderDelegate.h
//  rml
//
//  Created by plter on 9/5/14.
//  Copyright (c) 2014 plter. All rights reserved.
//

#ifndef rml_IRMLReaderDelegate_h
#define rml_IRMLReaderDelegate_h

#include <map>
#include "RMLObject.h"

namespace rml {
    class IReaderDelegate{
        
    public:
        virtual void documentStart(){};
        virtual void documentEnd(){};
        virtual void startElement(std::u16string & elementName,std::map<std::u16string, std::u16string> & attrs){};
        virtual void endElement(std::u16string & elementName){};
        virtual void foundText(std::u16string & text){};
        virtual void foundComment(std::u16string & comment){};
    };
}

#endif