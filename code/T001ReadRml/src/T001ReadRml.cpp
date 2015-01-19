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
#include <string>
#include <RMLReader.h>
#include <RMLIReaderDelegate.h>
#include <RMLObject.h>


class MyDelegate:public rml::Object,public rml::IReaderDelegate {

public:
    virtual void documentStart(rml::Reader * reader){
        printf("Start Doc\n");
    };
    virtual void documentEnd(rml::Reader * reader){
        printf("End Doc\n");
    };
    virtual void startElement(rml::Reader * reader,std::string & elementName,std::map<std::string, std::string> & attrs){

        std::cout<<"Start "<<elementName<<">>>>>\n";

        if (elementName.compare("person")==0) {
            std::cout<<"Name:"<<attrs["name"]<<",Age:"<<attrs["age"]<<"\n";
        }
    };
    virtual void endElement(rml::Reader * reader,std::string & elementName){
        std::cout<<"End "<<elementName<<"<<<<<\n";
    };
    virtual void foundText(rml::Reader * reader,std::string & text){
        std::cout<<"Text Content : "<<text<<"\n";
    };
    virtual void foundComment(rml::Reader * reader,std::string & comment){
        std::cout<<"Comment : "<<comment<<"\n";
    };

    MyDelegate(){};
    virtual ~MyDelegate(){};
};



int main(int argc, const char * argv[]) {

    std::ifstream f("data.xml");
    std::stringbuf sb;
    f>>&sb;
    f.close();

    std::string rmlData = sb.str();


    MyDelegate * delegate = new MyDelegate();
    rml::Reader r(rmlData,delegate);
    delegate->release();

    r.read();

    return 0;
}
