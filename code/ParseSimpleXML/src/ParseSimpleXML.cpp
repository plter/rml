//============================================================================
// Name        : ParseSimpleXML.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//
//  main.cpp
//  T001ReadRML
//
//  Created by plter on 9/5/14.
//  Copyright (c) 2014 plter. All rights reserved.
//

#include <iostream>
#include <iosfwd>
#include <string>
#include "RMLReader.h"
#include "RMLIReaderDelegate.h"
#include "RMLObject.h"


class MyDelegate:public rml::Object,public rml::IReaderDelegate {

public:
    virtual void documentStart(){
        printf("Start Doc\n");
    };
    virtual void documentEnd(){
        printf("End Doc\n");
    };
    virtual void startElement(std::string & elementName,std::map<std::string, std::string> & attrs){

        std::cout<<"Start "<<elementName<<"\n";

        if (elementName.compare("person")==0) {
            std::cout<<"Name:"<<attrs["name"]<<",Age:"<<attrs["age"]<<"\n";
        }
    };
    virtual void endElement(std::string & elementName){
        std::cout<<"End "<<elementName<<"\n";
    };
    virtual void foundText(std::string & text){
        std::cout<<"Text Content : "<<text<<"\n";
    };
    virtual void foundComment(std::string & comment){
        std::cout<<"Comment : "<<comment<<"\n";
    };
};



int main(int argc, const char * argv[]) {

    std::string rmlData = "<data><!--Hello 你好--><person age=\"20\" name=\"ZhangSan\">Haha</person><person name=\"Lisi\" age=\"18\"/></data>";


    MyDelegate * delegate = new MyDelegate();
    rml::Reader r(rmlData,delegate);
    delegate->release();

    r.read();

    return 0;
}
