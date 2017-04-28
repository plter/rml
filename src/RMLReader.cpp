/*
 * RMLReader.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: plter
 */

#include "RMLReader.h"


rml::Reader::Reader(std::string &rmlContent, IReaderDelegate *delegate) {

    _rmlContent = rmlContent;
    _delegate = delegate;
    _inCount = 0;
    _currentIndex = 0;
    _leftAngleBracketIndex = 0;
    _rightAngleBracketIndex = 0;
    _docEnded = false;

    dynamic_cast<rml::Object *>(_delegate)->retain();
}

rml::Reader::~Reader() {
    dynamic_cast<rml::Object *>(_delegate)->release();
}


void rml::Reader::read() {
    _inCount = 0;
    long size = _rmlContent.size();

    _delegate->documentStart(this);
    std::string currentStr;
    char currentC;
    _leftAngleBracketIndex = 0;
    _rightAngleBracketIndex = 0;
    _docEnded = false;

    for (_currentIndex = 0; _currentIndex < size && !_docEnded; ++_currentIndex) {

        if (_rmlContent[_currentIndex] == '<') {
            _leftAngleBracketIndex = _currentIndex;
            tryToFindContentText();

            currentStr = "";
            int j = 0;
            for (j = _currentIndex + 1; j < size && (currentC = _rmlContent[j]) != '>'; ++j) {
                currentStr += currentC;
            }
            _rightAngleBracketIndex = j;
            _currentIndex = j;

            parseTagContentString(currentStr);
        }
    }
}

void rml::Reader::startElement(std::string &elementName,
                               std::map<std::string, std::string> &attrs) {
    _inCount++;
    _delegate->startElement(this, elementName, attrs);
}

void rml::Reader::endElement(std::string &elementName) {
    _inCount--;

    _delegate->endElement(this, elementName);
    if (_inCount <= 0) {
        _delegate->documentEnd(this);
        _docEnded = true;
    }

}

void rml::Reader::parseTagContentString(std::string tagContentString) {

    char currentC;

    long currentStrSize = tagContentString.size();
    currentC = tagContentString[0];

    if (currentC == '/') { //end element
        std::string endElementName = tagContentString.substr(1, currentStrSize - 1);
        endElement(endElementName);
    } else if (currentC == '!') { //the currentStr is a comment
        std::string comment = tagContentString.substr(1, currentStrSize - 1);
        _delegate->foundComment(this, comment);
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
                        for (int b = a; b > 0 && (currentC =
                                                          tagContentString[b]) != ' '; --b) {
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
    if ((_leftAngleBracketIndex != 0) && (_rightAngleBracketIndex != 0) &&
        _leftAngleBracketIndex > _rightAngleBracketIndex + 1) {
        std::string contentText = _rmlContent.substr(_rightAngleBracketIndex + 1,
                                                     _leftAngleBracketIndex - _rightAngleBracketIndex - 1);
        _delegate->foundText(this, contentText);
    }
}
