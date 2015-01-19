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
#include "RMLReader.h"

namespace rml {
    
    class Reader;
    
    class IReaderDelegate{
        
    public:
        virtual void documentStart(Reader * reader){};
        virtual void documentEnd(Reader * reader){};
        virtual void startElement(Reader * reader,std::string & elementName,std::map<std::string, std::string> & attrs){};
        virtual void endElement(Reader * reader,std::string & elementName){};
        virtual void foundText(Reader * reader,std::string & text){};
        virtual void foundComment(Reader * reader,std::string & comment){};
        virtual ~IReaderDelegate(){};
    };
}

#endif
