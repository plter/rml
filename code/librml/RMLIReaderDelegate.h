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
        virtual void startElement(std::string & elementName,std::map<std::string, std::string> & attrs){};
        virtual void endElement(std::string & elementName){};
        virtual void foundText(std::string & text){};
        virtual void foundComment(std::string & comment){};
        virtual ~IReaderDelegate(){};
    };
}

#endif
