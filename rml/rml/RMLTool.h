//
//  RMLTool.h
//  rml
//
//  Created by plter on 9/6/14.
//  Copyright (c) 2014 plter. All rights reserved.
//

#ifndef rml_RMLTool_h
#define rml_RMLTool_h


#include <iostream>
#include <string>
#include <codecvt>

namespace rml {
    
    class Tool{
        
        
    public:
        static void trace(std::u16string & msg){
            static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> cvt;
            std::cout<<cvt.to_bytes(msg)<<"\n";
        };
    };
    
}

#endif
