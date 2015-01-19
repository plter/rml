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
        int32_t _inCount;
        uint32_t _currentIndex;
        int32_t _leftAngleBracketIndex;
        int32_t _rightAngleBracketIndex;
        bool _docEnded;

    private:
        void startElement(std::string & elementName,std::map<std::string, std::string> & attrs);
        void endElement(std::string & elementName);
        void parseTagContentString(std::string tagContentString);
        void tryToFindContentText();

    public:
        /********************************
         Construct a RMLReader object
         @param rmlContent  The rml file content
         @param delegate    The delegate to parse rml file
         ********************************/
        Reader(std::string & rmlContent,IReaderDelegate * delegate);
        virtual ~ Reader();

        void read();
    };
}

#endif
