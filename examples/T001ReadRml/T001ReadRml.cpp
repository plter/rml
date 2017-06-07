//============================================================================
// Name        : ParseSimpleRML.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <Reader.h>


class MyDelegate : public rml::IReaderDelegate {

public:
    void documentStart(rml::Reader &reader) override {
        std::cout << "Start Doc" << std::endl;
    };

    void documentEnd(rml::Reader &reader) override {
        std::cout << "End Doc" << std::endl;
    };

    void
    startElement(rml::Reader &reader, std::string &elementName, std::map<std::string, std::string> &attrs) override {

        std::cout << "Start " << elementName << ">>>>>\n";

        if (elementName == "person") {
            std::cout << "Name:" << attrs["name"] << ",Age:" << attrs["age"] << "\n";
        }
    };

    void endElement(rml::Reader &reader, std::string &elementName) override {
        std::cout << "End " << elementName << "<<<<<\n";
    };

    void foundText(rml::Reader &reader, std::string &text) override {
        std::cout << "Text Content : " << text << "\n";
    };

    void foundComment(rml::Reader &reader, std::string &comment) override {
        std::cout << "Comment : " << comment << "\n";
    };
};


int main(int argc, const char *argv[]) {

    std::ifstream f("data.xml");
    std::stringbuf sb;
    f >> &sb;
    f.close();

    std::string rmlData = sb.str();

    MyDelegate delegate;
    rml::Reader r(rmlData, delegate);
    r.read();

    return 0;
}
