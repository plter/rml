/*
 * RMLReader.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: plter
 */

#include "Reader.h"


rml::Reader::Reader(std::string &rmlContent, IReaderDelegate &delegate) :
        delegate(delegate),
        rmlContent(rmlContent),
        depth(0),
        currentIndex(0),
        leftAngleBracketIndex(0),
        rightAngleBracketIndex(0),
        docEnded(false) {
}


void rml::Reader::read() {
    depth = 0;
    long size = rmlContent.size();

    getDelegate().documentStart(*this);
    std::string currentStr;
    char currentC;
    leftAngleBracketIndex = 0;
    rightAngleBracketIndex = 0;
    docEnded = false;

    for (currentIndex = 0; currentIndex < size && !docEnded; ++currentIndex) {

        if (rmlContent[currentIndex] == '<') {
            leftAngleBracketIndex = currentIndex;
            tryToFindContentText();

            currentStr = "";
            uint32_t j = 0;
            for (j = currentIndex + 1; j < size && (currentC = rmlContent[j]) != '>'; ++j) {
                currentStr += currentC;
            }
            rightAngleBracketIndex = j;
            currentIndex = j;

            parseTagContentString(currentStr);
        }
    }
}

void rml::Reader::startElement(std::string &elementName,
                               std::map<std::string, std::string> &attrs) {
    depth++;
    getDelegate().startElement(*this, elementName, attrs);
}

void rml::Reader::endElement(std::string &elementName) {
    depth--;

    getDelegate().endElement(*this, elementName);
    if (depth <= 0) {
        getDelegate().documentEnd(*this);
        docEnded = true;
    }

}

void rml::Reader::parseTagContentString(std::string tagContentString) {

    char currentC;

    unsigned long currentStrSize = tagContentString.size();
    currentC = tagContentString[0];

    if (currentC == '/') { //end element
        std::string endElementName = tagContentString.substr(1, currentStrSize - 1);
        endElement(endElementName);
    } else if (currentC == '!') { //the currentStr is a comment
        std::string comment = tagContentString.substr(1, currentStrSize - 1);
        getDelegate().foundComment(*this, comment);
    } else { //start element

        std::map<std::string, std::string> attrs;
        std::string elementName;

        int k = 0;
        //read element name
        for (; k < currentStrSize && (currentC = tagContentString[k]) != ' '; ++k) {
            elementName += currentC;
        }

        //read kvs
        for (; k < currentStrSize; ++k) {

            if (tagContentString[k] == '=') {
                std::string key, value;

                //find key
                for (int a = k - 1; a > 0; --a) {
                    currentC = tagContentString[a];

                    if (currentC != ' ') {
                        for (int b = a; b > 0 && (currentC = tagContentString[b]) != ' '; --b) {
                            key += currentC;
                        }

                        std::string tmp = key;
                        //reverse the string
                        key.assign(tmp.rbegin(), tmp.rend());
                        break;
                    }
                }

                //find value
                for (int c = k; c < currentStrSize; ++c) {
                    currentC = tagContentString[c];

                    if (currentC == '"') {
                        for (int d = c + 1; d < currentStrSize && (currentC = tagContentString[d]) != '"'; ++d) {
                            value += currentC;

                            k = d;
                        }

                        break;
                    }
                }

                attrs[key] = value;
            }
        }

        startElement(elementName, attrs);
        if (tagContentString[currentStrSize - 1] == '/') {
            endElement(elementName);
        }
    }
}

void rml::Reader::tryToFindContentText() {
    if ((leftAngleBracketIndex != 0) && (rightAngleBracketIndex != 0) &&
        leftAngleBracketIndex > rightAngleBracketIndex + 1) {
        std::string contentText = rmlContent.substr(rightAngleBracketIndex + 1,
                                                    leftAngleBracketIndex - rightAngleBracketIndex - 1);
        getDelegate().foundText(*this, contentText);
    }
}

rml::IReaderDelegate &rml::Reader::getDelegate() const {
    return delegate;
}

void rml::Reader::setDelegate(rml::IReaderDelegate &delegate) {
    Reader::delegate = delegate;
}
