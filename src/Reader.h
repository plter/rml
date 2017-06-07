//
//  RMLReader.h
//  src
//
//  Created by plter on 9/5/14.
//  Copyright (c) 2014 plter. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>
#include "IReaderDelegate.h"
#include <map>
#include "RMLObject.h"

namespace rml {

    class IReaderDelegate;

    class Reader {

    private:
        std::string rmlContent;
        IReaderDelegate &delegate;
        uint32_t depth;
        uint32_t currentIndex;
        uint32_t leftAngleBracketIndex;
        uint32_t rightAngleBracketIndex;
        bool docEnded;

    private:
        void startElement(std::string &elementName, std::map<std::string, std::string> &attrs);

        void endElement(std::string &elementName);

        void parseTagContentString(std::string tagContentString);

        void tryToFindContentText();

    public:
        /**
         * Construct a RMLReader object
         * @param rmlContent The rml file content
         * @param delegate The delegate to parse rml file
         * @return
         */
        Reader(std::string &rmlContent, IReaderDelegate &delegate);

        void read();

        IReaderDelegate &getDelegate() const;

        void setDelegate(IReaderDelegate &delegate);
    };
}
