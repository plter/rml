/*
 * RMLArgContext.h
 *
 *  Created on: Jan 19, 2015
 *      Author: plter
 */

#ifndef RMLARGCONTEXT_H_
#define RMLARGCONTEXT_H_

#include "RMLValue.h"
#include "Context.h"

namespace rml {

    class ArgContext : public Context {
    public:
        ArgContext(Context *parent);

        virtual ~ArgContext();

    public:
        inline Value *getValue() {
            return _value;
        };

    public://delegate
        virtual void documentStart(Reader *reader);

        virtual void documentEnd(Reader *reader);

        virtual void startElement(Reader *reader, std::string &elementName, std::map<std::string, std::string> &attrs);

        virtual void endElement(Reader *reader, std::string &elementName);

        virtual void foundText(Reader *reader, std::string &text);

        virtual void foundComment(Reader *reader, std::string &comment);

    private:
        Value *_value;
    };

} /* namespace src */

#endif /* RMLARGCONTEXT_H_ */
