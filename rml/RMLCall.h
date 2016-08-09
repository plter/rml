/*
 * RMLCall.h
 *
 *  Created on: Jan 16, 2015
 *      Author: plter
 */

#pragma once

#include "RMLObject.h"
#include "RMLIReaderDelegate.h"
#include <string>
#include "RMLVector.h"
#include "RMLValue.h"
#include "context/RMLArgContext.h"

namespace rml {

    class Call : public Context {

    public:
        Call(Context *parent, std::string name);

        virtual ~Call();

    public:
        void pushArg(rml::Value *arg);

        void exec();

        rml::Value *at(uint32_t index);

        const std::string &getName() const {
            return _name;
        }

    public://override delegate
        virtual void documentStart(Reader *reader);

        virtual void documentEnd(Reader *reader);

        virtual void startElement(Reader *reader, std::string &elementName, std::map<std::string, std::string> &attrs);

        virtual void endElement(Reader *reader, std::string &elementName);

        virtual void foundText(Reader *reader, std::string &text);

        virtual void foundComment(Reader *reader, std::string &comment);

    private:
        std::string _name;
        rml::Vector<rml::Value *> _args;
        rml::ArgContext *_currentArgContext;
    };

} /* namespace rml */
