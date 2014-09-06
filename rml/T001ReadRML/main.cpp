//
//  main.cpp
//  T001ReadRML
//
//  Created by plter on 9/5/14.
//  Copyright (c) 2014 plter. All rights reserved.
//

#include <iostream>
#include "RMLReader.h"
#include "RMLReaderDelegate.h"
#include <codecvt>
#include "RMLTool.h"
#include "RMLObject.h"


class MyDelegate:public rml::Object,public rml::IReaderDelegate {
    
public:
    virtual void documentStart(){
        printf("Start Doc\n");
    };
    virtual void documentEnd(){
        printf("End Doc\n");
    };
    virtual void startElement(std::u16string & elementName,std::map<std::u16string, std::u16string> & attrs){
        static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> cvt;
        std::cout<<"Start "<<cvt.to_bytes(elementName)<<"\n";
        
        if (elementName.compare(u"person")==0) {
            std::cout<<"Name:"<<cvt.to_bytes(attrs[u"name"])<<",Age:"<<cvt.to_bytes(attrs[u"age"])<<"\n";
        }
    };
    virtual void endElement(std::u16string & elementName){
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> cvt;
        std::cout<<"End "<<cvt.to_bytes(elementName)<<"\n";
    };
    virtual void foundText(std::u16string & text){
        std::cout<<"Text Content : ";
        rml::Tool::trace(text);
    };
    virtual void foundComment(std::u16string & comment){
        std::cout<<"Comment : ";
        rml::Tool::trace(comment);
    };
};



int main(int argc, const char * argv[]) {
    
    std::u16string rmlData = u"<data><!--Hello 你好--><person age=\"20\" name=\"ZhangSan\">Haha</person></data>";
    
    MyDelegate * delegate = new MyDelegate();
    
    rml::Reader r(rmlData,delegate);
    delegate->release();
    
    r.read();
    
    return 0;
}
